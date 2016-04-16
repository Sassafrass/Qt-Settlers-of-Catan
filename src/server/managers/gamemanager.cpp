#include "shared/enums/command.h"
#include "shared/connection.h"
#include "shared/qout.h"
#include "server/enums/userstate.h"
#include "server/managers/gamemanager.h"
#include "server/user.h"
#include "server/game.h"
#include "shared/gameconfig.h"
#include "server/server.h"
#include "shared/defines.h"

GameManager::GameManager(CatanServer *server) :
    QObject(server), server(server)
{
    gameIDCounter = 0;
}

CatanServer* GameManager::GetServer() const
{
    return server;
}

void GameManager::CreateGame( CatanGameConfiguration *config,
                              const QVector<CatanPlayer*>& players )
{
    CatanGame *game = new CatanGame(this, gameIDCounter++, players, config);
    games[game->GetID()] = game;

    connect( game, SIGNAL(destroying()), this, SLOT(onGameDestroyed()));
}

CatanGame* GameManager::GetByID(GameID ID) const
{
    if( !games.contains(ID) )
        return 0;

    return games[ID];
}

void GameManager::onGameDestroyed()
{
    CatanGame *game = qobject_cast<CatanGame*>(sender());
    Q_ASSERT(game);

    net::Begin(NETWORK_COMMAND::SERVER_GAME_END);
    net::Send(*(game->GetPlayers()));

    games.remove(game->GetID());

    LOG_INFO( "Game [" << game->GetID() << "] has ended" << endl );
}
