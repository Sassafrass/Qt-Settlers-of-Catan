/****************************************************************************
** **Settlers of Catan**
** Development Card Enumeration
** author: Team Bronies
** date: 4/25/2012
**
** The lobby manager manages all of the CatanRooms on the server.
** it receives the network commands for creating a room, joining a room, or
** listing the current available rooms.
****************************************************************************/

#ifndef LOBBYMANAGER_H
#define LOBBYMANAGER_H

#include <QObject>
#include <QMap>

#include "server/managers/networkmanager.h"
#include "server/lobby.h"

class CatanUser;
class CatanServer;
class CatanGameConfiguration;
class Connection;

class LobbyManager : public QObject
{
    Q_OBJECT
public:
    explicit LobbyManager(CatanServer *server);
    CatanRoom* GetByID( RoomID ID ) const;
    CatanServer* GetServer() const;
signals:
    
public slots:
    //sent by a CatanUser when he requests to create a room
    void RequestCreateRoom( QString lobbyName, int maxPlayers = 4, bool randomChits = false, bool maritimeTrade = true );
    //sent by a CatanUser when he requests to join a room
    void RequestJoinRoom( RoomID lobbyID );
    //sent by a Catanuser when he requests to see a list of available rooms
    void RequestListRooms();
private slots:
    //sent by a CatanRoom when the room has been destroyed
    void onRoomDestroyed();
    //sent by a CatanRoom when the player-count of the room has changed
    void roomUpdate(CatanPlayer*);
private:
    CatanServer *server;
    void NewRoom( CatanUser* host, QString lobbyName, CatanGameConfiguration *config );
    QMap< RoomID, CatanRoom* > lobbies;
    int lobbyIDCounter;
};

#endif // LOBBYMANAGER_H
