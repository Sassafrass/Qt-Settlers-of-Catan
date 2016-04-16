/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QTimerEvent>
#include "shared/connection.h"

static const int TransferTimeout = 30 * 1000;
static const int PongTimeout = 60 * 1000;
static const int PingInterval = 1 * 1000;
static const char SeparatorToken = ' ';

Connection::Connection(QObject *parent)
    : QTcpSocket(parent)
{
    state = WaitingForGreeting;
    numBytesForCurrentCommand = -1;
    currentCommand = NETWORK_COMMAND::NONE;
    transferTimerId = 0;
    pingTimer.setInterval(PingInterval);

    QObject::connect(this, SIGNAL(readyRead()), this, SLOT(processReadyRead()));
    QObject::connect(this, SIGNAL(disconnected()), &pingTimer, SLOT(stop()));
    QObject::connect(this, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    QObject::connect(&pingTimer, SIGNAL(timeout()), this, SLOT(sendPing()));
}

void Connection::sendPing()
{

    if (pongTime.elapsed() > PongTimeout) {
        abort();
        return;
    }

    if( state != ReadyForUse )
        return;

    QByteArray block;
    QDataStream in(&block, QIODevice::WriteOnly);
    in.setVersion(QDataStream::Qt_4_8);

    in << (quint8)NETWORK_COMMAND::PING;
    in << (quint16)0;

    write(block);

}

void Connection::sendPong()
{

    QByteArray block;
    QDataStream in(&block, QIODevice::WriteOnly);
    in.setVersion(QDataStream::Qt_4_8);

    in << (quint8)NETWORK_COMMAND::PONG;
    in << (quint16)0;

    write(block);

}

void Connection::timerEvent(QTimerEvent *timerEvent)
{
    if (timerEvent->timerId() == transferTimerId) {
        abort();
        killTimer(transferTimerId);
        transferTimerId = 0;
    }
}

void Connection::processReadyRead()
{
    if (state == WaitingForGreeting) {
        if (!readProtocolHeader())
            return;
        if (currentCommand != NETWORK_COMMAND::GREETING) {
            abort();
            return;
        }
        state = ReadingGreeting;
    }

    if (state == ReadingGreeting) {
        if (!hasEnoughData())
            return;

        currentCommand = NETWORK_COMMAND::NONE;
        numBytesForCurrentCommand = -1;
        buffer.clear();

        if (!isValid()) {
            abort();
            return;
        }
        state = ReadyForUse;
        emit readyForUse();

        pingTimer.start();
        pongTime.start();
    }

    do {
        if (currentCommand == NETWORK_COMMAND::NONE) {
            if (!readProtocolHeader())
                return;
        }
        if (!hasEnoughData())
            return;
        processData();
    } while (bytesAvailable() > 0);
}

int Connection::dataLengthForCurrentCommand()
{
    if (bytesAvailable() < (int)sizeof(quint16))
        return 0;

    QDataStream in(this);
    in >> numBytesForCurrentCommand;
    return numBytesForCurrentCommand;
}

bool Connection::readProtocolHeader()
{
    if (transferTimerId) {
        killTimer(transferTimerId);
        transferTimerId = 0;
    }

    if (bytesAvailable() < (int)sizeof(quint8)) {
        transferTimerId = startTimer(TransferTimeout);
        return false;
    }

    QDataStream in(this);
    in >> currentCommand;

    if ( currentCommand >= NETWORK_COMMAND::NONE )
    {
        transferTimerId = startTimer(TransferTimeout);
        return false;
    }

    buffer.clear();
    numBytesForCurrentCommand = dataLengthForCurrentCommand();
    return true;
}

bool Connection::hasEnoughData()
{
    if (transferTimerId) {
        QObject::killTimer(transferTimerId);
        transferTimerId = 0;
    }

    if (numBytesForCurrentCommand == (quint16)(-1))
        numBytesForCurrentCommand = dataLengthForCurrentCommand();

    if (bytesAvailable() < numBytesForCurrentCommand
            || numBytesForCurrentCommand == (quint16)(-1)) {
        transferTimerId = startTimer(TransferTimeout);
        return false;
    }

    return true;
}

void Connection::processData()
{
    if( numBytesForCurrentCommand > 0 )
    {
        buffer = read(numBytesForCurrentCommand);
        if (buffer.size() != numBytesForCurrentCommand) {
            abort();
            return;
        }
    }

    if( currentCommand == NETWORK_COMMAND::PING )
    {
        sendPong();
    }
    else if( currentCommand == NETWORK_COMMAND::PONG )
    {
        pongTime.restart();
    }
    else if( currentCommand != NETWORK_COMMAND::GREETING )
    {
        QDataStream in(&buffer, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_4_8);
        emit receivedCommand(static_cast<NetworkCommand>(currentCommand), in);
    }

    currentCommand = NETWORK_COMMAND::NONE;
    numBytesForCurrentCommand = -1;
    buffer.clear();
}

void Connection::onDisconnected()
{
    currentCommand = NETWORK_COMMAND::NONE;
    numBytesForCurrentCommand = -1;
    buffer.clear();
    state = WaitingForGreeting;
}
