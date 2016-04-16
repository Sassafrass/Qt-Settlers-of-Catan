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

#ifndef TILE_H
#define TILE_H

#include <QMap>
#include <QPoint>

#include "shared/enums/direction.h"
#include "shared/enums/terrain.h"
#include "shared/entities/base.h"

class CatanBoard;
class CatanChit;
class CatanTileVertex;

/**
 * Generates the terrain tiles for the game board.
 **/
class CatanTile : public Entity
{
public:
    CatanTile(CatanBoard* board);
    ~CatanTile();  //deletes the CatanTile

    /**
     * Sets the type of terrain
     * @param enumerated terrain type
     **/
    void SetTerrain(const TERRAIN::ENUM &type);

    /**
     * Sets the position of the terrain tiles
     * @param const QPoint &pos
     **/
    void SetTilePos(const QPoint &pos);

    /**
     * Sets the position of the terrain tiles
     * @param const int x
     * @param const int y
     **/
    void SetTilePos(const int x, const int y);

    /**
     * Gets the value of each token
     * @return const value
     **/
    int GetTokenValue() const;

    /**
     * Sets the value of each token
     * @param int value
     **/
    void SetTokenValue(int value);
    void SetYaw(int yaw);

    TERRAIN::ENUM GetType() const;
    QList<CatanTileVertex*> GetVertices() const;
    QMap<DIRECTION::ENUM, CatanTile*> GetAdjacentTiles() const;
    CatanTile* GetDN() const;  //adjacent down
    CatanTile* GetUP() const;  //adjacent up
    CatanTile* GetLL() const;  //adjacent lower left
    CatanTile* GetUL() const;  //adjacent upper left
    CatanTile* GetLR() const;  //adjacent lower right
    CatanTile* GetUR() const;  //adjacent upper right
    int GetX() const;  //x coordinate
    int GetY() const;  //y coordinate
    int GetYaw() const;
    CatanBoard* GetBoard() const;

private:

    CatanBoard* board;
    CatanChit* chit;
    int tokenValue;  //token value
    QPoint tilePos;     //tile position
    TERRAIN::ENUM type;  //enumeration type
    int yaw;
};

#endif // TILE_H
