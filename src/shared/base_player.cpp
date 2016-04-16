#include "shared/base_player.h"
#include "shared/entities/piece.h"
#include "shared/entities/settlement.h"
#include "shared/entities/city.h"
#include "shared/entities/road.h"

#define CATAN_PLAYER_SETTLEMENT_COUNT 5
#define CATAN_PLAYER_ROAD_COUNT 15
#define CATAN_PLAYER_CITY_COUNT 5

CatanPlayerBase::CatanPlayerBase(PlayerID ID, QObject *parent) :
    QObject(parent), ID(ID)
{
    color = PLAYER_COLOR::NONE;

    //set up the player's hand
    hand = new PlayerHand(this);

    createPieces();
}

void CatanPlayerBase::createPieces()
{
    //create settlements
    for( int i = 0; i < CATAN_PLAYER_SETTLEMENT_COUNT; i++ )
    {
        passivePieces.push_back( new CatanSettlement(this) );
    }

    //create cities
    for( int i = 0; i < CATAN_PLAYER_CITY_COUNT; i++ )
    {
        passivePieces.push_back( new CatanCity(this) );
    }

    //create roads
    for( int i = 0; i < CATAN_PLAYER_ROAD_COUNT; i++ )
    {
        passivePieces.push_back( new CatanRoad(this) );
    }
}

QString CatanPlayerBase::GetName() const
{
    return name;
}

PlayerID CatanPlayerBase::GetID() const
{
    return ID;
}

PLAYER_STATE::ENUM CatanPlayerBase::GetState() const
{
    return state;
}

QList<CatanPiece*> CatanPlayerBase::GetActivePieces() const
{
    return activePieces;
}

QList<CatanSettlement*> CatanPlayerBase::GetSettlements() const
{
    QList<CatanSettlement*> settlements;
    foreach( CatanPiece *piece, GetActivePieces() )
    {
        CatanSettlement *settlement = qobject_cast<CatanSettlement*>(piece);
        if( settlement )
            settlements.push_back(settlement);
    }

    return settlements;
}

void CatanPlayerBase::AddResource(RESOURCE::ENUM res, int count)
{
    GetPlayerHand()->AddResource(res, count);
}

PlayerHand* CatanPlayerBase::GetPlayerHand() const
{
    return hand;
}

void CatanPlayerBase::SetState( PLAYER_STATE::ENUM state )
{
    this->state = state;
}

PlayerColor CatanPlayerBase::GetColor() const
{
    return color;
}

void CatanPlayerBase::SetColor(const PlayerColor& color)
{
    this->color = color;
}

CatanPlayerBase::~CatanPlayerBase()
{
}
