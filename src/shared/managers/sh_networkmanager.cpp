#include "shared/managers/sh_networkmanager.h"
#include "shared/qout.h"
#include "shared/connection.h"

NetworkManager* NetworkManager::instance_ = 0;

NetworkManager* NetworkManager::getInstance()
{
    if( !instance_ )
        instance_ = new NetworkManager();
    return instance_;
}

void NetworkManager::Begin(NetworkCommand e)
{
    //make sure we aren't already building a network message
    if( stream )
    {
        LOG_ERROR("Attempting to start a new network message before sending a previous one." << endl);
        return;
    }

    stream = new QDataStream(&buffer, QIODevice::WriteOnly);
    stream->setVersion(QDataStream::Qt_4_8);

    *stream << (quint8)e;
    *stream << (quint16)0;
}

void net::Begin(NetworkCommand e)
{
    NetworkManager::getInstance()->Begin(e);
}

void net::AddByte(quint8 c)
{
    NetworkManager::getInstance()->AddByte(c);
}

void net::AddBool(bool b)
{
    NetworkManager::getInstance()->AddBool(b);
}

void net::AddChar(QChar c)
{
    NetworkManager::getInstance()->AddChar(c);
}

void net::AddString(QString s)
{
    NetworkManager::getInstance()->AddString(s);
}

void net::AddShort(quint16 s)
{
    NetworkManager::getInstance()->AddShort(s);
}

void NetworkManager::AddByte(quint8 c)
{
    Q_ASSERT( stream );
    *stream << c;
}

void NetworkManager::AddBool(bool b)
{
    Q_ASSERT( stream );
    *stream << b;
}

void NetworkManager::AddChar(QChar c)
{
    Q_ASSERT( stream );
    *stream << c;
}

void NetworkManager::AddString(QString s)
{
    Q_ASSERT( stream );
    *stream << s;
}

void NetworkManager::AddShort(quint16 s)
{
    Q_ASSERT( stream );
    *stream << s;
}

void NetworkManager::Send(const QList<Connection*> &rf)
{
    //stream the size of the block
    stream->device()->seek(1);
    *stream << (quint16)(buffer.size() - sizeof(quint16) - sizeof(quint8));

    //send the block
    foreach( Connection* conn, rf )
    {
        if( !conn )
            return;

        if( !conn->write(buffer) )
        {
            LOG_ERROR("Error writing to connection" << endl);
            return;
        }
    }

    //clear the block
    buffer.clear();
    delete stream;
    stream = 0;
}

void NetworkManager::Send(Connection* conn)
{
    QList<Connection*> rf;
    rf.push_back(conn);
    Send( rf );
}
