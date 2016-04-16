#include "edge.h"
#include "vertex.h"
#include "board.h"
#include "tile.h"
#include "socket.h"
#include "road.h"

CatanTileEdge::CatanTileEdge(CatanBoard *board, const QPoint& pos) :
    CatanTileSocket(board, pos, pos.y() % 3 == 0 ? -120 : ((pos.y() + 1) % 3 == 0 ? 120 : 0))
{

}

CatanRoad* CatanTileEdge::GetRoad() const
{
    return qobject_cast<CatanRoad*>(piece);
}

QList<CatanTileVertex*> CatanTileEdge::GetAdjacentVertices() const
{
    QList<CatanTileVertex*> adjacentVerts;

    if( GetY() % 3 == 0 ) {
        adjacentVerts.push_back( board->GetVertexAt( GetX(), GetY() * 2 / 3 - 1 ) );
        adjacentVerts.push_back( board->GetVertexAt( GetX(), GetY() * 2 / 3 ) );
    } else if( (GetY() - 1) % 3 == 0 ) {
        adjacentVerts.push_back( board->GetVertexAt( GetX()    , (GetY() - 1) * 2 / 3 ) );
        adjacentVerts.push_back( board->GetVertexAt( GetX() + 1, (GetY() - 1) * 2 / 3 + 1 ) );
    } else {
        adjacentVerts.push_back( board->GetVertexAt( GetX(), (GetY() - 2) * 2 / 3 ) );
        adjacentVerts.push_back( board->GetVertexAt( GetX(), (GetY() - 2) * 2 / 3 + 1 ) );
    }

    return adjacentVerts;
}

QList<CatanTileEdge*> CatanTileEdge::GetAdjacentEdges() const
{
    QList<CatanTileEdge*> adjacentEdges;

    if( GetY() % 3 == 0 ) {
        adjacentEdges.push_back( board->GetEdgeAt( GetX() - 1, GetY() - 2 ) );
        adjacentEdges.push_back( board->GetEdgeAt( GetX()    , GetY() - 1 ) );
        adjacentEdges.push_back( board->GetEdgeAt( GetX()    , GetY() + 2 ) );
        adjacentEdges.push_back( board->GetEdgeAt( GetX()    , GetY() + 1 ) );
    } else if( (GetY() - 1) % 3 == 0 ) {
        adjacentEdges.push_back( board->GetEdgeAt( GetX()    , GetY() + 1 ) );
        adjacentEdges.push_back( board->GetEdgeAt( GetX()    , GetY() - 1 ) );
        adjacentEdges.push_back( board->GetEdgeAt( GetX() + 1, GetY() + 2 ) );
        adjacentEdges.push_back( board->GetEdgeAt( GetX() + 1, GetY() + 1 ) );
    } else {
        adjacentEdges.push_back( board->GetEdgeAt( GetX()    , GetY() + 1 ) );
        adjacentEdges.push_back( board->GetEdgeAt( GetX() - 1, GetY() - 1 ) );
        adjacentEdges.push_back( board->GetEdgeAt( GetX()    , GetY() - 1 ) );
        adjacentEdges.push_back( board->GetEdgeAt( GetX()    , GetY() - 2 ) );
    }

    return adjacentEdges;
}
