/****************************************************************************
** **Settlers of Catan**
** CatanTile Entity Class
** author: Frank Sasto / Dore Weber
** date: 3/27/2012
**
** A CatanTile is a hexagonal entity representing terrain in the world of
** Catan.  Each tile has a terrain type, which can be resourceful, or not.
** There are 5 resource tiles: Mountain, Hill, Pasture, Forest, and Field.
** The only other land tile which is not a resource is the desert tile.
** The desert tile has no chit.
** The world is bordered by non-resource water tiles.  A water tile can
** be a port for maritime trading.
****************************************************************************/

#include "shared/entities/tile.h"
#include "shared/entities/board.h"
#include "shared/entities/chit.h"
#include "shared/entities/vertex.h"
#include "shared/sh_util.h"

CatanTile::CatanTile(CatanBoard *board )
    : Entity(board), board(board)
{
    type = TERRAIN::WATER;
    tokenValue = 0;
    chit = 0;
    yaw = 0;
}

CatanTile::~CatanTile()
{
}

void CatanTile::SetYaw(int yaw)
{
    this->yaw = yaw;
}

int CatanTile::GetYaw() const
{
    return yaw;
}

int CatanTile::GetTokenValue() const
{
    return tokenValue;
}

void CatanTile::SetTokenValue(int value)
{
    tokenValue = value;
    if( chit )
        chit->SetValue(value);
}

void CatanTile::SetTilePos(const QPoint &pos)
{
    tilePos = pos;
}

void CatanTile::SetTilePos(const int x, const int y)
{
    tilePos.setX(x);
    tilePos.setY(y);
}

void CatanTile::SetTerrain(const TERRAIN::ENUM &type)
{
    this->type = type;
    if( TERRAIN::HasChit(type) )
    {
        if( !chit )
        {
            chit = new CatanChit();
        }
    }
    else if( chit )
    {
        delete chit;
        tokenValue = 0;
        chit = 0;
    }
}

TERRAIN::ENUM CatanTile::GetType() const
{
    return type;
}

CatanBoard* CatanTile::GetBoard() const
{
    return board;
}

QList<CatanTileVertex*> CatanTile::GetVertices() const
{
    QList<CatanTileVertex*> adjacentVertices;
    return adjacentVertices;
}

QMap<DIRECTION::ENUM, CatanTile*> CatanTile::GetAdjacentTiles() const
{
    QMap<DIRECTION::ENUM, CatanTile*> adjacentTiles;
    CatanTile* tile;
    tile = GetUP();
    if( tile )
        adjacentTiles[ DIRECTION::UP ] = tile;
    tile = GetDN();
    if( tile )
        adjacentTiles[ DIRECTION::DN ] = tile;
    tile = GetLL();
    if( tile )
        adjacentTiles[ DIRECTION::LL ] = tile;
    tile = GetUL();
    if( tile )
        adjacentTiles[ DIRECTION::UL ] = tile;
    tile = GetLR();
    if( tile )
        adjacentTiles[ DIRECTION::LR ] = tile;
    tile = GetUR();
    if( tile )
        adjacentTiles[ DIRECTION::UR ] = tile;

    return adjacentTiles;
}

CatanTile* CatanTile::GetDN() const
{
    return GetBoard()->GetTileAt( GetX(), GetY() - 1 );
}
CatanTile* CatanTile::GetUP() const
{
    return GetBoard()->GetTileAt( GetX(), GetY() + 1 );
}
CatanTile* CatanTile::GetLL() const
{
    return GetBoard()->GetTileAt( GetX() - 1, GetY() - 1 );
}
CatanTile* CatanTile::GetUL() const
{
    return GetBoard()->GetTileAt( GetX() - 1, GetY() );
}
CatanTile* CatanTile::GetLR() const
{
    return GetBoard()->GetTileAt( GetX() + 1, GetY() );
}
CatanTile* CatanTile::GetUR() const
{
    return GetBoard()->GetTileAt( GetX() + 1, GetY() + 1 );
}
int CatanTile::GetX() const
{
    return tilePos.x();
}
int CatanTile::GetY() const
{
    return tilePos.y();
}
