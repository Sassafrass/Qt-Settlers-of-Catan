#include "user.h"
#include "server/client.h"
#include "server/entities/player.h"
#include "shared/qout.h"

CatanUser::CatanUser(QObject *parent) :
    QObject(parent), connection(0)
{
    state = USER_STATE::DISCONNECTED;
    player = 0;
}

QString CatanUser::name() const
{
    return username;
}

USER_STATE::ENUM CatanUser::GetState() const
{
    return state;
}

ClientConnection* CatanUser::GetConnection() const
{
    return connection;
}

CatanPlayer* CatanUser::GetPlayer() const
{
    return player;
}

bool CatanUser::InLobby() const
{
    if( !player )
        return false;

    return player->GetState() == PLAYER_STATE::IN_LOBBY;
}

bool CatanUser::InGame() const
{
    if( !player )
        return false;

    return player->GetState() == PLAYER_STATE::IN_GAME;
}

void CatanUser::SetState( USER_STATE::ENUM state )
{
    this->state = state;
}

void CatanUser::SetPlayer(CatanPlayer *player)
{
    this->player = player;
    connect( player, SIGNAL(destroyed()),
             this, SLOT(onPlayerDestroyed()));
}

void CatanUser::onPlayerDestroyed()
{
    player = 0;
}

void CatanUser::SetConnection(ClientConnection* conn)
{
    this->connection = conn;
    state = USER_STATE::CONNECTED;
    connect( conn, SIGNAL(disconnected()), this, SLOT(onDisconnected()) );
    connect( conn, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onConnectionError(QAbstractSocket::SocketError)));

    connect( conn, SIGNAL(receivedCommand(NetworkCommand,QDataStream&)),
             this, SLOT(onReceivedCommand(NetworkCommand,QDataStream&)));
}

void CatanUser::onDisconnected()
{
    if (ClientConnection *connection = qobject_cast<ClientConnection *>(sender()))
        removeConnection(connection);

    emit disconnected();
}

void CatanUser::onConnectionError(QAbstractSocket::SocketError /* socketError */)
{
    if (ClientConnection *connection = qobject_cast<ClientConnection *>(sender()))
        removeConnection(connection);
}

void CatanUser::onReceivedCommand(NetworkCommand cmd, QDataStream &in)
{
    if( cmd == NETWORK_COMMAND::CLIENT_NAME )
    {
        QString name;
        in >> name;
        if( !username.isEmpty() )
            return;
        username = name;
        emit authenticated();
    }
    else if( !username.isEmpty() )
    {
        switch( cmd )
        {
        case NETWORK_COMMAND::CLIENT_LIST:
        {
            LOG_DEBUG("Client [" << name() << "] requests a list of the rooms." << endl);
            emit RequestListRooms();
            break;
        }
        case NETWORK_COMMAND::CLIENT_CREATE:
        {
            QString title;
            quint8 players;
            bool maritimeTrade;
            bool randomChits;
            in >> title;
            in >> players;
            in >> maritimeTrade;
            in >> randomChits;
            LOG_DEBUG("Client [" << name() << "] requests to create room.\n" <<
                      "\tLobby name: " << title << "\n" <<
                      "\tPlayers: " << players << endl);
            emit RequestCreateRoom( title, players, randomChits, maritimeTrade );
            break;
        }
        case NETWORK_COMMAND::CLIENT_JOIN:
        {
            RoomID lobbyID;
            in >> lobbyID;
            LOG_DEBUG("Client [" << name() << "] requests to join room.\n" <<
                      "\tLobby ID#: " << lobbyID << endl);
            emit RequestJoinRoom(lobbyID);
            break;
        }
        default:
        {
            break;
        }
        }
    }
}

void CatanUser::removeConnection(ClientConnection *connection)
{
    state = USER_STATE::DISCONNECTED;
    connection->SetUser(0);
    connection->deleteLater();
    this->connection = 0;
}
