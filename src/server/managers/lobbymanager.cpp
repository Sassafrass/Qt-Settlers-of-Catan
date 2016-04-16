#include "shared/enums/command.h"
#include "shared/connection.h"
#include "shared/gameconfig.h"
#include "shared/defines.h"
#include "shared/qout.h"
#include "server/managers/lobbymanager.h"
#include "server/enums/userstate.h"
#include "server/user.h"
#include "server/lobby.h"
#include "server/server.h"

LobbyManager::LobbyManager(CatanServer *server) :
    QObject(server), server(server)
{
    lobbyIDCounter = 0;
}

CatanServer* LobbyManager::GetServer() const
{
    return server;
}

void LobbyManager::NewRoom( CatanUser* host, QString lobbyName, CatanGameConfiguration *config )
{
    CatanRoom *lobby = new CatanRoom( this, lobbyIDCounter++, host, lobbyName, config );
    lobbies[lobby->GetID()] = lobby;

    net::Begin(NETWORK_COMMAND::SERVER_ROOM_NEW);
        net::AddShort(lobby->GetID());
        net::AddString(lobby->GetGameName());
        net::AddByte(lobby->GetMaxPlayers());
    net::Send(server->GetUsers());

    connect( lobby, SIGNAL(destroying()), this, SLOT(onRoomDestroyed()));
    connect( lobby, SIGNAL(addedPlayer(CatanPlayer*)), this, SLOT(roomUpdate(CatanPlayer*)));
    connect( lobby, SIGNAL(removedPlayer(CatanPlayer*)), this, SLOT(roomUpdate(CatanPlayer*)));
    LOG_INFO( "User (" << host->name() << ") has created a new lobby: " << lobby->GetID() << endl );
}

void LobbyManager::onRoomDestroyed()
{
    CatanRoom *lobby = qobject_cast<CatanRoom*>(sender());

    Q_ASSERT(lobby);

    net::Begin(NETWORK_COMMAND::SERVER_ROOM_CLOSE);
        net::AddShort(lobby->GetID());
    net::Send(server->GetUsers());

    lobbies.remove(lobby->GetID());

    LOG_INFO( "Room [" << lobby->GetID() << "] has been removed" << endl );
}

void LobbyManager::roomUpdate(CatanPlayer*)
{
    CatanRoom *room = qobject_cast<CatanRoom*>(sender());
    Q_ASSERT(room);

    if( room->GetNumPlayers() > 0 )
    {
        net::Begin(NETWORK_COMMAND::SERVER_ROOM_UPDATE);
            net::AddShort(room->GetID());
            net::AddByte(room->GetNumPlayers());
        net::Send(server->GetUsers());
    }
}

void LobbyManager::RequestCreateRoom(QString lobbyName, int maxPlayers,
                                     bool randomChits, bool maritimeTrading)
{
    CatanUser *user = qobject_cast<CatanUser*>(sender());
    if( !user )
        return;

    if( user->GetState() != USER_STATE::CONNECTED )
        return; //you cannot make a lobby if you're already in a lobby or game.

    if( user->InGame() || user->InLobby() )
        return;

    CatanGameConfiguration *config = new CatanGameConfiguration(this);
    config->SetMaxPlayers(maxPlayers);
    config->SetRandomChits(randomChits);
    config->SetMaritimeTrading(maritimeTrading);

    //Shorten the name
    if( lobbyName.length() > 30 )
        lobbyName = lobbyName.left(30).append("...");

    //game must be 4 - 6 players, the gui has
    //enforced this and the client has sent us bad data.
    //Don't let them create a lobby.
    if( maxPlayers < CATAN_MIN_PLAYERS || maxPlayers > CATAN_MAX_PLAYERS )
        return;

    NewRoom( user, lobbyName, config );
}

void LobbyManager::RequestJoinRoom(RoomID lobbyID)
{
    CatanUser *user = qobject_cast<CatanUser*>(sender());
    if( !user )
        return;

    if( user->InGame() || user->InLobby() )
        return;

    CatanRoom *lobby = GetByID(lobbyID);
    if( !lobby )
    {
        net::Begin(NETWORK_COMMAND::SERVER_ROOM_NONEXISTANT);
        net::Send(user);
        return;
    }

    if( !lobby->AddUser(user) )
    {
        net::Begin(NETWORK_COMMAND::SERVER_ROOM_FULL);
        net::Send(user);
    }
}

void LobbyManager::RequestListRooms()
{
    CatanUser *user = qobject_cast<CatanUser*>(sender());
    if( !user ) return;

    if( user->InGame() || user->InLobby() )
        return;

    //TODO: Implement some sort of request timer, so clients
    //cannot send requests too fast (this timer needs to be serverside)

    net::Begin(NETWORK_COMMAND::SERVER_ROOM_LIST);
        net::AddShort( lobbies.size() );
        foreach( CatanRoom *lobby, lobbies )
        {
            net::AddShort( lobby->GetID() );
            net::AddString( lobby->GetGameName() );
            net::AddByte( lobby->GetNumPlayers() );
            net::AddByte( lobby->GetMaxPlayers() );
        }
    net::Send((Connection*)user->GetConnection());
}

CatanRoom* LobbyManager::GetByID(RoomID ID) const
{
    if( !lobbies.contains(ID) )
        return 0;

    return lobbies[ID];
}
