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

#include <algorithm>
#include <QPair>
#include <QDateTime>
#include <QDebug>
#include "board.h"
#include "tile.h"
#include "edge.h"
#include "vertex.h"
#include "server/game.h"
#include "shared/defines.h"

static const QPair<TERRAIN::ENUM,int> resource_counts_4_players[6] = {
    QPair<TERRAIN::ENUM,int>(TERRAIN::DESERT, 1),
    QPair<TERRAIN::ENUM,int>(TERRAIN::HILLS, 3),
    QPair<TERRAIN::ENUM,int>(TERRAIN::PASTURE, 4),
    QPair<TERRAIN::ENUM,int>(TERRAIN::MOUNTAINS, 3),
    QPair<TERRAIN::ENUM,int>(TERRAIN::FIELDS, 4),
    QPair<TERRAIN::ENUM,int>(TERRAIN::FOREST, 4)
};

static const int tile_count_4_players = 19;
static const int tiles_setup_4_players[tile_count_4_players][2] = {
            { 0, 2}, { 1, 2}, { 2, 2},
        {-1, 1}, { 0, 1}, { 1, 1}, { 2, 1},
    {-2, 0}, {-1, 0}, { 0, 0}, { 1, 0}, { 2, 0},
        {-2,-1}, {-1,-1}, { 0,-1}, { 1,-1},
            {-2,-2}, {-1,-2}, { 0,-2},
};

static const int chit_count_4_players = 18;
static const int chits_4_players[chit_count_4_players] = {
    2,
    3, 3,
    4, 4,
    5, 5,
    6, 6,
    8, 8,
    9, 9,
    10, 10,
    11, 11,
    12
};

static const int tile_count_6_players = 30;
static const int tiles_setup_6_players[tile_count_6_players][2] = {
                { 0, 3}, { 1, 3}, { 2, 3},
            {-1, 2}, { 0, 2}, { 1, 2}, { 2, 2},
        {-2, 1}, {-1, 1}, { 0, 1}, { 1, 1}, { 2, 1},
    {-3, 0}, {-2, 0}, {-1, 0}, { 0, 0}, { 1, 0}, { 2, 0},
        {-3,-1}, {-2,-1}, {-1,-1}, { 0,-1}, { 1,-1},
            {-3,-2}, {-2,-2}, {-1,-2}, { 0,-2},
                {-3,-3}, {-2,-3}, {-1,-3},
};

static const QPair<TERRAIN::ENUM,int> resource_counts_6_players[6] = {
    QPair<TERRAIN::ENUM,int>(TERRAIN::DESERT, 2),
    QPair<TERRAIN::ENUM,int>(TERRAIN::HILLS, 5),
    QPair<TERRAIN::ENUM,int>(TERRAIN::PASTURE, 6),
    QPair<TERRAIN::ENUM,int>(TERRAIN::MOUNTAINS, 5),
    QPair<TERRAIN::ENUM,int>(TERRAIN::FIELDS, 6),
    QPair<TERRAIN::ENUM,int>(TERRAIN::FOREST, 6)
};

static const int chit_count_6_players = 28;
static const int chits_6_players[chit_count_6_players] = {
    2, 2,
    3, 3, 3,
    4, 4, 4,
    5, 5, 5,
    6, 6, 6,
    8, 8, 8,
    9, 9, 9,
    10, 10, 10,
    11, 11, 11,
    12, 12,
};

CatanBoard::CatanBoard(QObject *parent, uint seed) :
    Entity(parent), seed(seed)
{
}

CatanBoard::~CatanBoard()
{
}

void CatanBoard::SetNumPlayers(int count)
{
    Q_ASSERT(count >= CATAN_MIN_PLAYERS && count <= CATAN_MAX_PLAYERS);
    players = count;
    extension = count == 6;
}

CatanTile* CatanBoard::createTile()
{
    return new CatanTile(this);
}

void CatanBoard::createTiles()
{
    int tileCount = (extension ? tile_count_6_players : tile_count_4_players );

    //Create needed tiles
    for( int i = tiles.size(); i < tileCount; i++ )
    {
        tiles.push_back(createTile());
    }
    //Delete extra tiles
    while( tileCount < tiles.size() )
    {
        delete tiles.back();
        tiles.pop_back();
    }
    //Assign tile terrains
    int index = 0;
    for( int i = 0; i < 6; i++ )
    {
        if( extension )
        {
            QPair<TERRAIN::ENUM,int> p = resource_counts_6_players[i];
            for( int j = 0; j < p.second; j++ )
            {
                tiles[index++]->SetTerrain( p.first );
            }
        }
        else
        {
            QPair<TERRAIN::ENUM,int> p = resource_counts_4_players[i];
            for( int j = 0; j < p.second; j++ )
            {
                tiles[index++]->SetTerrain( p.first );
            }
        }
    }
}

CatanTileVertex* CatanBoard::GetVertexAt(const int x, const int y)
{
    QPoint pos(x, y);
    if( !vertexMap.contains(pos) )
        return 0;
    return vertexMap[pos];
}

CatanTileEdge* CatanBoard::GetEdgeAt(const int x, const int y)
{
    QPoint pos(x, y);
    if( !edgeMap.contains(pos) )
        return 0;
    return edgeMap[pos];
}

CatanTile* CatanBoard::GetTileAt(const int x, const int y)
{
    QPoint pos(x, y);
    if( !tileMap.contains(pos) )
        return 0;
    return tileMap[pos];
}

const QVector<CatanTile*>& CatanBoard::GetTiles() const
{
    return tiles;
}

void CatanBoard::SetupTiles()
{
    //set the seed
    qsrand(seed);

    //Create tiles
    tileMap.clear();
    createTiles();

    //Shuffle the tiles
    qsrand( QDateTime::currentMSecsSinceEpoch() );
    std::random_shuffle( tiles.begin(), tiles.end() );

    //Create chits
    int chitCount = (extension ? chit_count_6_players : chit_count_4_players);
    QVector<int> chits;

    for (int i = 0; i < chitCount; i++)
    {
        chits.push_back(extension ? chits_6_players[i] : chits_4_players[i]);
    }

    std::random_shuffle(chits.begin(), chits.end());

    //Place tiles
    int chit_i = 0;
    if( extension )//6 player board
    {
        for( int i = 0; i < tile_count_6_players; i++ )
        {
            QPoint pos = QPoint(tiles_setup_6_players[i][0],tiles_setup_6_players[i][1]);
            CatanTile* tile = tiles[i];
            tileMap[pos] = tiles[i];
            tile->SetTilePos( pos );
            tile->SetYaw( 60 * (int)(qrand()%6) );
            if( TERRAIN::HasChit(tile->GetType()))
                tile->SetTokenValue(chits[chit_i++]);
        }
    }
    else
    {
        for( int i = 0; i < tile_count_4_players; i++ )
        {
            QPoint pos = QPoint(tiles_setup_4_players[i][0],tiles_setup_4_players[i][1]);
            CatanTile* tile = tiles[i];
            tileMap[pos] = tiles[i];
            tile->SetTilePos(pos);
            tile->SetYaw( 60 * (int)(qrand()%6) );
            if( TERRAIN::HasChit(tile->GetType()))
                tile->SetTokenValue(chits[chit_i++]);
        }
    }

    foreach( CatanTile *tile, tiles )
    {
        createTileVertices(tile);
        createTileEdges(tile);
    }

    //Fix Adjacent Red Chits
    fixAdjacentHighChits();
    //Create Water Tiles
    QSet<CatanTile*> checked;
    createWaterTiles( GetTileAt( 0, 0 ), checked );
}

//6 vertexs per hexagon
static const int vertex_offsets[6][2] = {
            {-1, 0}, { 0, 1}, { 0, 0},
        { 0,-1}, {-1,-2}, {-1,-1}
};

void CatanBoard::createTileVertices( CatanTile *tile )
{
    for( int i = 0; i < 6; i++ )
    {
        int px = tile->GetX() + vertex_offsets[i][0];
        int py = tile->GetY()*2 + vertex_offsets[i][1];

        CatanTileVertex *vert = GetVertexAt( px, py );
        if( !vert )
        {
            vert = new CatanTileVertex(this, QPoint(px, py));
            vertexMap[vert->GetPos()] = vert;
        }
    }
}

//6 edges per hexagon
static const int edge_offsets[6][2] = {
            {-1, 1}, { 0, 2}, { 0, 0},
        {-1,-2}, {-1,-1}, {-1, 0}
};

void CatanBoard::createTileEdges( CatanTile *tile )
{
    for( int i = 0; i < 6; i++ )
    {
        int px = tile->GetX() + edge_offsets[i][0];
        int py = tile->GetY()*3 + edge_offsets[i][1];

        CatanTileEdge *edge = GetEdgeAt( px, py );
        if( !edge )
        {
            edge = new CatanTileEdge(this, QPoint(px, py));
            edgeMap[edge->GetPos()] = edge;
        }
    }
}

void CatanBoard::fixAdjacentHighChits()
{
    foreach( CatanTile* tile, tiles )
    {
        //if this tile has a red chit
        if( tile->GetTokenValue() == 6 || tile->GetTokenValue() == 8 )
        {
            //for each adjacent tile check if there is an adjacent red chit
            foreach(CatanTile const* t1, tile->GetAdjacentTiles().values())
            {
                //if this adjacent tile has a red chit
                if( (t1->GetTokenValue() == 6 || t1->GetTokenValue() == 8) )
                {
                    //find a tile to swap
                    foreach( CatanTile* t2, tiles )
                    {
                        if( t2 != tile && t2->GetTokenValue() != 0 && t2->GetTokenValue() != 6 && t2->GetTokenValue() != 8 )
                        {
                            bool bSwappable = true;
                            //if this tile has an adjacent red chit, we cannot swap with it.
                            foreach( CatanTile const* t3, t2->GetAdjacentTiles().values() )
                            {
                                if( t3 != tile && (t3->GetTokenValue() == 6 || t3->GetTokenValue() == 8) )
                                {
                                    bSwappable = false;
                                    break;
                                }
                            }

                            if( bSwappable )
                            {
                                //swap these tiles
                                int tempValue = tile->GetTokenValue();
                                tile->SetTokenValue(t2->GetTokenValue());
                                t2->SetTokenValue(tempValue);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

void CatanBoard::createWaterTiles( CatanTile* curTile, QSet<CatanTile*> &checked )
{
    //make sure we don't check this tile again.
    checked.insert( curTile );

    //Store pointers to each  "Get<DIRECTION>()" member function of the tile
    typedef CatanTile* (CatanTile::*CTileGetFunc)() const;
    typedef QPair<DIRECTION::ENUM,CTileGetFunc> DirFunc;
    const DirFunc directions[6] = {
        DirFunc(DIRECTION::UP,&CatanTile::GetUP),
        DirFunc(DIRECTION::DN,&CatanTile::GetDN),
        DirFunc(DIRECTION::LL,&CatanTile::GetLL),
        DirFunc(DIRECTION::LR,&CatanTile::GetLR),
        DirFunc(DIRECTION::UL,&CatanTile::GetUL),
        DirFunc(DIRECTION::UR,&CatanTile::GetUR)
    };
    //loop through each direction function
    for( int i = 0; i < 6; i ++ )
    {
        //Get the tile adjacent to the current tile in this direction
        CatanTile* tile = (curTile->*(directions[i].second))();

        //If there is no tile in this direction
        if( tile == 0 )
        {
            //create a water tile
            tile = createWaterTile( curTile->GetX(), curTile->GetY(), directions[i].first );
            //make sure we don't check this tile again.
            checked.insert( tile );
        }
        else if( !checked.contains( tile ) )
        { //recursively check this tile's adjacent tiles for potential land border.
            createWaterTiles( tile, checked );
        }
    }
}

CatanTile* CatanBoard::createWaterTile( int posX, int posY, const DIRECTION::ENUM &dir )
{
    //offset the current tile position in the direction
    if( dir == DIRECTION::UP || dir == DIRECTION::UR )
        posY += 1;
    if( dir == DIRECTION::DN || dir == DIRECTION::LL )
        posY -= 1;
    if( dir == DIRECTION::LR || dir == DIRECTION::UR )
        posX += 1;
    if( dir == DIRECTION::LL || dir == DIRECTION::UL )
        posX -= 1;

    //orient the new water tile's yaw to point to the previous tile
    int yaw = 0;
    if( dir == DIRECTION::UR )
        yaw -= 60;
    else if( dir == DIRECTION::LR )
        yaw -= 120;
    else if( dir == DIRECTION::DN )
        yaw -= 180;
    else if( dir == DIRECTION::LL )
        yaw += 120;
    else if( dir == DIRECTION::UL )
        yaw += 60;

    //create water tile with a 30% chance of being a port
    CatanTile* tile = createTile();
    tile->SetTerrain( rand()%10 > 3 ?
            TERRAIN::WATER :
            static_cast<TERRAIN::ENUM>(TERRAIN::WATER + (int)(rand()%7)) );
    tile->SetTilePos( posX, posY );
    tile->SetYaw( yaw );

    //add the new tile to the map
    tiles.push_back( tile );
    tileMap[QPoint(posX,posY)] = tile;

    return tile;

}
