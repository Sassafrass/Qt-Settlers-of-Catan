#include "server/lobby.h"
#include "server/entities/player.h"
#include "server/user.h"
#include "server/server.h"
#include "shared/gameconfig.h"

#include "server/managers/lobbymanager.h"
#include "server/managers/networkmanager.h"
#include "server/managers/gamemanager.h"
#include "shared/qout.h"

RoomID getNextPID( CatanPlayer* players[CATAN_MAX_PLAYERS] )
{
    //get the next unique player id for this lobby
    //(this isn't expensive since there's only 6 players max)
    RoomID id = 0;
    for( int i = 0; i < CATAN_MAX_PLAYERS; i++ )
    {
        if( players[i] )
            id++;
    }
    return id;
}

CatanRoom::CatanRoom(LobbyManager *manager, RoomID ID, CatanUser *creator, QString displayName,
                       CatanGameConfiguration *config ) :
    QObject(manager), manager(manager), ID(ID), displayname(displayName), config(config)
{
    playerCount = 0;
    host = 0;
    for( int i = 0; i < CATAN_MAX_PLAYERS; i++ )
    {
       players[i] = 0;
       readyPlayers[i] = false;
    }
    AddUser( creator );

    connect( &startTimer, SIGNAL(timeout()),
             this, SLOT(startGame()));
}


QVector<CatanPlayer*> CatanRoom::getPlayers() const
{
    QVector<CatanPlayer*> playerList;
    for( int i = 0; i < GetMaxPlayers(); i++ )
    {
        if( players[i] )
            playerList.push_back(players[i]);
    }
    return playerList;
}

QString CatanRoom::GetGameName() const
{
    return displayname;
}

RoomID CatanRoom::GetID() const
{
    return ID;
}

quint8 CatanRoom::GetMaxPlayers() const
{
    return config->GetMaxPlayers();
}

quint8 CatanRoom::GetNumPlayers() const
{
    return playerCount;
}

void CatanRoom::setHost( CatanPlayer *host )
{
    this->host = host;
    connect( host, SIGNAL(requestStartGame()),
             this,   SLOT(requestStartGame()));
    connect( host, SIGNAL(requestChangeConfig(QDataStream&)),
             this,  SLOT(receivedChangeConfig(QDataStream&)));
}

void CatanRoom::transmitConfigFull( CatanUser *user )
{
    net::Begin(NETWORK_COMMAND::SERVER_ROOM_CONFIG_FULL);
        net::AddByte(config->GetMaxPlayers());
        net::AddBool(config->GetRandomChits());
        net::AddBool(config->GetMaritimeTrading());
    net::Send(user);
}

void CatanRoom::receivedChangeConfig( QDataStream& /*msg*/ )
{
    //CatanPlayer *player = qobject_cast<CatanPlayer*>(sender());
    //Q_ASSERT(player);


}

bool CatanRoom::AddUser( CatanUser *user )
{
    if( GetNumPlayers() >= config->GetMaxPlayers() ) return false;
    if( user->InGame() || user->InLobby() ) return false;

    int id = getNextPID( players );
    CatanPlayer* player = new CatanPlayer(id, user, this);

    //set the host
    if( !host )
        setHost( player );

    players[id] = player;
    playerCount++;

    LOG_DEBUG( "Lobby player count: " << GetNumPlayers() << endl );
    player->SetState(PLAYER_STATE::IN_LOBBY);

    //tell the current players in the room that this user has joined
    for( int i = 0; i < GetMaxPlayers(); i++ )
    {
        CatanPlayer *occupant = players[i];
        if( !occupant ) continue;

        net::Begin(NETWORK_COMMAND::SERVER_ROOM_USER_JOINED);
            net::AddShort(this->GetID());
            net::AddByte(player->GetID());
            net::AddString(player->GetName());
        net::Send(occupant->GetUser());
    }

    //tell this user about the current players in the room
    net::Begin(NETWORK_COMMAND::SERVER_ROOM_PLAYERS);
        net::AddByte(GetNumPlayers()-1); //don't include the new player
        //send the host first.
        net::AddByte(host->GetID());
        net::AddString(host->GetName());
        net::AddBool(readyPlayers[host->GetID()]);
        for( int i = 0; i < GetMaxPlayers(); i++ )
        {
            CatanPlayer *occupant = players[i];
            if( !occupant ) continue;

            if( occupant != host && occupant != player )
            {
                net::AddByte(occupant->GetID());
                net::AddString(occupant->GetName());
                net::AddBool(readyPlayers[occupant->GetID()]);
            }
        }
    net::Send(user);

    //send the game configuration
    transmitConfigFull(user);

    //if the user gets destroyed, remove him from the room
    connect( player, SIGNAL(destroying()),
             this, SLOT(onPlayerDestroying()));
    connect( player, SIGNAL(requestLeaveRoom()),
             this, SLOT(onPlayerLeave()));
    connect( player, SIGNAL(readyUp(bool)),
             this, SLOT(readyUp(bool)));

    emit addedPlayer(player);
    return true;

}

void CatanRoom::requestStartGame()
{
    CatanPlayer *player = qobject_cast<CatanPlayer*>(sender());
    Q_ASSERT(player);

    if( !player ) return;
    if( player != host ) return; //only the host can begin the game
    if( startTimer.isActive() ) return; //the game is already being started
    if( GetNumPlayers() < CATAN_MIN_PLAYERS ) return; //cannot start with less than 4 players
    //check to make sure everyone is ready.
    for( int i = 0; i < GetMaxPlayers(); i++ )
    {
        CatanPlayer *occupant = players[i];
        if( !occupant ) continue;

        if( !readyPlayers[occupant->GetID()] )
            return; //cannot start the game unless all players are ready.
    }

    startTimer.setSingleShot(true);
    startTimer.start( CATAN_ROOM_START_TIME * 1000 );

    net::Begin(NETWORK_COMMAND::SERVER_ROOM_STARTING);
    net::Send(getPlayers());
}

void CatanRoom::readyUp(bool ready)
{
    CatanPlayer *player = qobject_cast<CatanPlayer*>(sender());
    Q_ASSERT(player);

    //make sure this player is still in the room.
    if( players[player->GetID()] != player ) return;

    //if the ready status has changed, network it to the other players
    if( ready == readyPlayers[player->GetID()] ) return;

    //send the message
    net::Begin(NETWORK_COMMAND::SERVER_ROOM_PLAYER_READY);
        net::AddByte(player->GetID());
        net::AddBool(ready);
    net::Send(getPlayers());

    readyPlayers[player->GetID()] = ready;
    if( !ready ) cancelStartup(player);
}

void CatanRoom::cancelStartup(CatanPlayer *player)
{
    //if we changed to un-ready and the game was starting, halt the game start timer
    if( startTimer.isActive() )
    {
        startTimer.stop();
        net::Begin(NETWORK_COMMAND::SERVER_ROOM_START_INTERRUPT);
            net::AddByte(player->GetID());
        net::Send(getPlayers());
    }
}

void CatanRoom::onPlayerLeave()
{
    LOG_DEBUG("Player leaving" << endl);
    CatanPlayer *player = qobject_cast<CatanPlayer*>(sender());
    Q_ASSERT(player);
    RemovePlayer( player );
}

void CatanRoom::onPlayerDestroying()
{
    LOG_DEBUG("Player object destroyed" << endl);
    CatanPlayer *player = qobject_cast<CatanPlayer*>(sender());
    Q_ASSERT(player);
    RemovePlayer( player );
}

void CatanRoom::RemovePlayer( CatanPlayer *player )
{
    disconnect( player, SIGNAL(requestLeaveRoom()),
                this, SLOT(onPlayerLeave()));
    disconnect( player, SIGNAL(destroyed()),
                this, SLOT(onPlayerDestroying()));

    if( players[player->GetID()] != player ) return;

    LOG_DEBUG("[Lobby " << GetID() << "] Removing player: " << player->GetName() << endl);

    //remove the player
    players[player->GetID()] = 0;
    readyPlayers[player->GetID()] = false;
    playerCount--;

    cancelStartup(player);
    emit removedPlayer(player);

    //remove this room if it is empty
    if( GetNumPlayers() == 0 )
    {
        player->deleteLater();
        this->deleteLater();
        return;
    }

    //get a list of all the players to send the message to
    QVector<CatanPlayer*> playerList = getPlayers();

    if( player == host ) //if this was the host
    {

        //remove the previous host
        disconnect( player, SIGNAL(requestStartGame()),
                    this,     SLOT(requestStartGame()));
        disconnect( player, SIGNAL(requestChangeConfig(QDataStream&)),
                    this,    SLOT(receivedChangeConfig(QDataStream&)));
        host = 0;

        //set the host to the next player in the list
        LOG_INFO("The host disconnected from lobby [" << (quint16)GetID() << "]" << endl);
        for( int i = 0; i < GetMaxPlayers(); i++ )
        {
            if( players[i] )
            {
                setHost(players[i]);
                break;
            }
        }
        if( host ) {
            LOG_DEBUG("New lobby host: " << host->GetName() << endl);
            net::Begin(NETWORK_COMMAND::SERVER_ROOM_NEW_HOST);
                net::AddByte(host->GetID());
            net::Send(playerList);
        }
    }

    //send the message
    net::Begin(NETWORK_COMMAND::SERVER_ROOM_USER_EXITED);
        net::AddByte(player->GetID());
    net::Send(playerList);

    player->deleteLater();
}

void CatanRoom::startGame()
{
    LOG_INFO("Game has started for room " << GetID() << endl);
    manager->GetServer()->GetGameManager()->CreateGame( config, getPlayers() );
    deleteLater();
}

CatanRoom::~CatanRoom()
{
    emit destroying();
}
