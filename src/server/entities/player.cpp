#include <QTimer>
#include "server/entities/player.h"
#include "server/user.h"
#include "shared/connection.h"

CatanPlayer::CatanPlayer(PlayerID ID, CatanUser *user, QObject *parent) :
    CatanPlayerBase(ID, parent), user(user)
{
    user->SetPlayer(this);
    this->name = user->name();
    connect( (Connection*)user->GetConnection(), SIGNAL(receivedCommand(NetworkCommand,QDataStream&)),
             this, SLOT(onReceivedCommand(NetworkCommand,QDataStream&)));
    connect( user, SIGNAL(destroyed()),
             this, SLOT(deleteLater()));
}

void CatanPlayer::RollDice()
{
    int rollDuration = qrand() % 500 + 1000; //in milliseconds
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->start(rollDuration);
    connect( timer, SIGNAL(timeout()),
             this, SIGNAL(rolledDice()));
}

void CatanPlayer::onReceivedCommand(NetworkCommand cmd, QDataStream &msg)
{
    switch(cmd)
    {
    case NETWORK_COMMAND::PLAYER_READY:
    {
        bool ready;
        msg >> ready;
        emit readyUp(ready);
        break;
    }
    case NETWORK_COMMAND::PLAYER_START:
    {
        emit requestStartGame();
        break;
    }
    case NETWORK_COMMAND::PLAYER_CHANGE_CONFIG:
    {
        emit requestChangeConfig(msg);
        break;
    }
    case NETWORK_COMMAND::PLAYER_LEAVE:
    {
        emit requestLeaveRoom();
        break;
    }
    default:
    {
        break;
    }
    }
}

CatanUser* CatanPlayer::GetUser() const
{
    return user;
}

CatanPlayer::~CatanPlayer()
{
    emit destroying();
}
