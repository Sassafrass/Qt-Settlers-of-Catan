#include "vertex.h"
#include "board.h"
#include "tile.h"
#include "edge.h"
#include "socket.h"
#include "settlement.h"

CatanTileVertex::CatanTileVertex(CatanBoard *board, const QPoint& pos) :
    CatanTileSocket(board, pos, qrand() % 12 * 30)
{
}

CatanSettlement* CatanTileVertex::GetSettlement() const
{
    return qobject_cast<CatanSettlement*>(piece);
}

QList<CatanTileVertex*> CatanTileVertex::GetAdjacentVertices() const
{
    QList<CatanTileVertex*> adjacentVerts;

    if( GetY() % 2 == 0 ) {
        adjacentVerts.push_back( board->GetVertexAt( GetX()     , GetY() - 1 ) );
        adjacentVerts.push_back( board->GetVertexAt( GetX()     , GetY() + 1 ) );
        adjacentVerts.push_back( board->GetVertexAt( GetX() + 1 , GetY() + 1 ) );
    } else {
        adjacentVerts.push_back( board->GetVertexAt( GetX() - 1 , GetY() - 1 ) );
        adjacentVerts.push_back( board->GetVertexAt( GetX()     , GetY() + 1 ) );
        adjacentVerts.push_back( board->GetVertexAt( GetX()     , GetY() - 1 ) );
    }

    return adjacentVerts;
}

QList<CatanTileEdge*> CatanTileVertex::GetAdjacentEdges() const
{
    QList<CatanTileEdge*> adjacentEdges;

    if( GetY() % 2 == 0 ) {
        adjacentEdges.push_back( board->GetEdgeAt( GetX(), GetY() / 2 * 3 ) );
        adjacentEdges.push_back( board->GetEdgeAt( GetX(), GetY() / 2 * 3 + 1 ) );
        adjacentEdges.push_back( board->GetEdgeAt( GetX(), GetY() / 2 * 3 + 2 ) );
    } else {
        adjacentEdges.push_back( board->GetEdgeAt( GetX() - 1   , (GetY() - 1) / 2 * 3 + 1 ) );
        adjacentEdges.push_back( board->GetEdgeAt( GetX()       , (GetY() - 1) / 2 * 3 + 2 ) );
        adjacentEdges.push_back( board->GetEdgeAt( GetX()       , (GetY() - 1) / 2 * 3 + 3 ) );
    }

    return adjacentEdges;
}

QList<CatanTile*> CatanTileVertex::GetAdjacentTiles() const
{
    QList<CatanTile*> adjacentTiles;

    if( GetY() % 2 == 0 ) {
        adjacentTiles.push_back( board->GetTileAt( GetX()       ,  GetY() / 2 ) );
        adjacentTiles.push_back( board->GetTileAt( GetX() + 1   ,  GetY() / 2 ) );
        adjacentTiles.push_back( board->GetTileAt( GetX() + 1   ,  GetY() / 2 + 1 ) );
    } else {
        adjacentTiles.push_back( board->GetTileAt( GetX()       ,  (GetY() - 1) / 2 + 1 ) );
        adjacentTiles.push_back( board->GetTileAt( GetX()       ,  (GetY() - 1) / 2 ) );
        adjacentTiles.push_back( board->GetTileAt( GetX() + 1   ,  (GetY() - 1) / 2 + 1 ) );
    }

    return adjacentTiles;
}
