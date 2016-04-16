/****************************************************************************
** **Settlers of Catan**
** Development Card Enumeration
** author: Team Bronies
** date: 4/25/2012
**
** The CatanUser is a wrapper for the CatanPlayer and ClientConnection.
** The purpose of the user is to associate a client connection to a player
** so that if a client disconnects and re-connects, they may be re-associated
** with that player.
** If a client disconnects and is not in a game, then the user is removed for
** that client.
****************************************************************************/

#ifndef USER_H
#define USER_H

#include <QObject>
#include <QAbstractSocket>

#include "shared/enums/command.h"
#include "shared/enums/playerstate.h"
#include "server/enums/userstate.h"
#include "server/lobby.h"

class ClientConnection;

class CatanPlayer;

class CatanUser : public QObject
{
    Q_OBJECT
public:
    explicit CatanUser(QObject *parent = 0);
    void SetConnection(ClientConnection* connection);
    void SetPlayer(CatanPlayer *player);
    void SetState(USER_STATE::ENUM state);
    ClientConnection* GetConnection() const;
    CatanPlayer* GetPlayer() const;
    USER_STATE::ENUM GetState() const;
    PLAYER_STATE::ENUM GetPlayerState() const;
    bool InLobby() const;
    bool InGame() const;
    QString name() const;
signals:
    void authenticated();
    void disconnected();
    void RequestCreateRoom(const QString &name,
                           int playerCount,
                           bool randomChits,
                           bool maritimeTrade);
    void RequestJoinRoom(RoomID lobbyID);
    void RequestListRooms();
    void receivedCommand(NetworkCommand,QDataStream&);
private slots:
    void onReceivedCommand(NetworkCommand,QDataStream&);
    void onDisconnected();
    void removeConnection(ClientConnection *connection);
    void onConnectionError(QAbstractSocket::SocketError /* socketError */);
    void onPlayerDestroyed();
private:
    ClientConnection* connection;
    QString username;
    USER_STATE::ENUM state;
    CatanPlayer *player;
};

#endif // USER_H
