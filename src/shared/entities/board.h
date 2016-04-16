/****************************************************************************
** **Settlers of Catan**
** CatanBoard Entity
** author: Frank Sasto / Dore Weber
** date: 3/27/2012
**
** This entity is responsible for generating a valid, random Catan board
** for 4 or 6 players.  The board displays many different terrain tiles
** surrounded by water tiles.  Each tile that is not a desert has a chit
** on it with a number representing a possible dice roll.
****************************************************************************/

#ifndef CATANBOARD_H
#define CATANBOARD_H

#include <QObject>
#include <QMap>
#include <QPoint>
#include <QVector>
#include <QPoint>

#include "shared/enums/direction.h"
#include "shared/entities/base.h"

class CatanTile;
class CatanTileEdge;
class CatanTileVertex;

/**
 * Comparison operator for QPoint objects.
 * Used for sorting QMap of QPoints.
 * @param QPoint &p1
 * @param QPoint &p2
 * @return true if p1 is less than p2
 **/
inline bool operator<(const QPoint &p1, const QPoint &p2)
{
    if( p1.x() != p2.x() )
        return p1.x() < p2.x();
    return p1.y() < p2.y();
}

/**
 * Generates a valid random Catan Board.
 **/
class CatanBoard : public Entity
{
public:
    explicit CatanBoard(QObject *parent, uint seed);
    ~CatanBoard();  //deletes CatanBoard

    /**
     * Sets the number of players for the game.
     * @param count
     **/
    void SetNumPlayers(int count);

    /**
     * Generates a new random board seeded with the
     * current epoche time.
     **/
    void SetupTiles();

    const QVector<CatanTile*>& GetTiles() const;

    /**
     * Gets the tile at the specified hex coordinate.
     * @param const int x coord
     * @param const int y coord
     * @returns CatanTile* tile at coordinate if exists or 0
     **/
    CatanTile* GetTileAt( const int x, const int y );
    /**
     * Gets the vertex at the specified vertex coordinate.
     * @param const int x coord
     * @param const int y coord
     * @returns CatanTileVertex* vertex at coordinate if exists or 0
     **/
    CatanTileVertex* GetVertexAt(const int x, const int y);
    /**
     * Gets the edge at the specified edge coordinate.
     * @param const int x coord
     * @param const int y coord
     * @returns CatanTileEdge* edge at coordinate if exists or 0
     **/
    CatanTileEdge* GetEdgeAt(const int x, const int y);
signals:
    
public slots:
    
private:

    uint seed;
    /**
     * Generates the tiles for each resource.
     **/
    void createTiles();

    void createTileVertices(CatanTile *tile);
    void createTileEdges(CatanTile *tile);

    /**
     * Ensures no two red chit tiles are placed
     * adjacently to one another.
     **/
    void fixAdjacentHighChits();

    /**
     * Generates the water tiles.
     * @param CatanTile* tile, QSet<CatanTile*> &checked
     **/
    void createWaterTiles( CatanTile* tile, QSet<CatanTile*> &checked );

    CatanTile* createWaterTile( int posX, int posY, const DIRECTION::ENUM &dir );
    CatanTile* createTile();

    int players; //number of players in the game
    bool extension; //true if the game has more than 4 players
    QMap<QPoint,CatanTile*> tileMap; //map of Hex coordinates to tiles
    QMap<QPoint,CatanTileEdge*> edgeMap; //map of tile edges
    QMap<QPoint,CatanTileVertex*> vertexMap; //map of tile vertices
    QVector<CatanTile*> tiles; //all of the tiles on the board

};

#endif // CATANBOARD_H
