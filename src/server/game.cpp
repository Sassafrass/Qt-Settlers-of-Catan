#include <QTime>
#include "game.h"
#include "server/managers/turnmanager.h"
#include "server/managers/gamemanager.h"
#include "shared/entities/board.h"
#include "shared/entities/tile.h"
#include "shared/entities/vertex.h"
#include "shared/entities/settlement.h"
#include "shared/gameconfig.h"
#include "shared/qout.h"
#include "shared/enums/playercolor.h"

CatanGame::CatanGame(GameManager *manager, GameID ID,
                     const QVector<CatanPlayer*>& players,
                     CatanGameConfiguration *config) :
    QObject(manager), manager(manager),
    ID(ID), players(players), config(config)
{
    LOG_INFO( "Game " << ID << " has been created." << endl);

    //update states
    setState(GAME_STATE::TURN_ORDER);
    foreach( CatanPlayer *player, players )
    {
        player->SetState(PLAYER_STATE::IN_GAME);
        player->setParent(this);
    }

    //create the board
    uint boardSeed = QTime::currentTime().msec();
    board = new CatanBoard(this, boardSeed);
    board->SetNumPlayers(players.size());
    board->SetupTiles();

    //initialize the turn order
    turnManager = new TurnManager(this, players);

    connect( turnManager, SIGNAL(orderDetermined()),
             this, SLOT(beginSetup()));
    connect( turnManager, SIGNAL(setupComplete()),
             this, SLOT(endSetup()));

    //assign each player a color
    //TODO: Let players choose themselves
    assignColors();

    //tell the clients the game has begun
    net::Begin(NETWORK_COMMAND::SERVER_GAME_START);
        net::AddShort(boardSeed);
        net::AddByte(players.size());
        foreach( CatanPlayer *player, players )
        {
            net::AddByte(player->GetID());
            net::AddByte(static_cast<quint8>(player->GetColor()));
            net::AddString(player->GetName());
        }
    net::Send(players);
}

GAME_STATE::ENUM CatanGame::GetState() const
{
    return state;
}

void CatanGame::setState(GAME_STATE::ENUM newState)
{
    state = newState;
    LOG_INFO( "[Game: " << GetID() << "] state is now " << newState << endl);
}

void CatanGame::beginSetup()
{
    if( state != GAME_STATE::TURN_ORDER ) return;

    setState( GAME_STATE::SETUP );
}

void CatanGame::endSetup()
{
    if( state != GAME_STATE::SETUP ) return;

    setState( GAME_STATE::STRIFE );

    //give the initial starting resources for each player
    //based on their occupied tiles.
    foreach( CatanPlayer *player, players )
    {
        foreach( CatanSettlement *settlement, player->GetSettlements() )
        {
            CatanTileVertex *vert = settlement->GetVertex();
            Q_ASSERT( vert );

            foreach( CatanTile *tile, vert->GetAdjacentTiles() )
            {
                if( TERRAIN::HasChit( tile->GetType() ) )
                {
                    player->AddResource( TERRAIN::ToResource( tile->GetType() ) );
                }
            }
        }
    }
}

const QVector<CatanPlayer*>* CatanGame::GetPlayers() const
{
    return &players;
}

GameID CatanGame::GetID() const
{
    return ID;
}

void CatanGame::assignColors()
{
    int playerColor = 0;
    foreach( CatanPlayer *player, players )
    {
        player->SetColor(static_cast<PlayerColor>(playerColor++));
    }
}

void CatanGame::phasePayout(int roll)
{
    foreach( CatanTile* tile, board->GetTiles() )
    {
        if( tile->GetTokenValue() == roll )
        {
            foreach( CatanTileVertex* vert, tile->GetVertices() )
            {
                CatanSettlement* settlement = vert->GetSettlement();
                if( settlement )
                {
                    settlement->GetOwner()->AddResource(
                        TERRAIN::ToResource(tile->GetType()),
                        settlement->IsCity() ? 2 : 1);
                }
            }
        }
    }
}

void CatanGame::phaseRobber()
{

}

CatanGame::~CatanGame()
{
    emit destroying();
}
