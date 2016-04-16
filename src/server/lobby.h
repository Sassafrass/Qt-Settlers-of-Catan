/****************************************************************************
** **Settlers of Catan**
** Development Card Enumeration
** author: Team Bronies
** date: 4/25/2012
**
** The CatanRoom represents a virtual lobby where players can group up
** and start a game of Catan.  In the lobby, the game configurations are
** changeable, the player colors are too.  When all players are ready,
** the host of the room can begin the game.
****************************************************************************/

#ifndef LOBBY_H
#define LOBBY_H

#include <QObject>
#include <QVector>
#include <QTimer>
#include <QDataStream>
#include "shared/defines.h"
#include "shared/enums/gameconfig.h"

class CatanPlayer;
class CatanUser;
class CatanGameConfiguration;
class LobbyManager;

typedef quint16 RoomID;

class CatanRoom : public QObject
{
    Q_OBJECT
public:
    explicit CatanRoom(LobbyManager *manager, RoomID ID, CatanUser *host, QString displayname,
                       CatanGameConfiguration *config);
    virtual ~CatanRoom();
signals:
    //emitted in the destructor
    void destroying();
    //emitted when a new player has been added
    void addedPlayer(CatanPlayer*);
    //emitted when a player has been removed
    void removedPlayer(CatanPlayer*);
public slots:
private slots:
    //sent by a CatanPlayer that is being destroyed
    void onPlayerDestroying();
    //sent by a CatanPlayer who has requested to leave the room
    void onPlayerLeave();
    //sent by a CatanPlayer who has toggled his ready status
    void readyUp(bool);
    void requestStartGame(); //player requests to start game
    //the game start timer has elapsed
    void startGame();
    //sent by a CatanPlaeyr who has changed the config
    void receivedChangeConfig(QDataStream&);
private: //variables
    LobbyManager *manager; //the manager of this room
    CatanPlayer* players[CATAN_MAX_PLAYERS]; //the players in this room
    RoomID ID; //unique ID number of this room
    QString displayname;
    CatanGameConfiguration *config;
    CatanPlayer *host; //the room king
    quint8 playerCount; //number of players in the room
    QTimer startTimer; //countdown timer for starting the game
    bool readyPlayers[CATAN_MAX_PLAYERS]; //map of playerID to ready status
private: //methods
    QVector<CatanPlayer*> getPlayers() const; //returns players in the room
    void setHost(CatanPlayer *host); //sets the room's host to a new player
    void transmitConfigFull( CatanUser *user ); //sends the configuration to a user
    void cancelStartup( CatanPlayer *player ); //cancels the game startup timer
public: //methods
    //returns true if player was successfully added to the lobby
    bool AddUser( CatanUser *user );
    void RemovePlayer( CatanPlayer *player );
    QString GetGameName() const;
    RoomID GetID() const;
    quint8 GetNumPlayers() const;
    quint8 GetMaxPlayers() const;
};

#endif // LOBBY_H
