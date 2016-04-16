#include "road.h"
#include "edge.h"
#include "shared/base_player.h"

CatanRoad::CatanRoad(CatanPlayerBase *owner) :
    CatanPiece(owner), edge(0)
{
}

CatanTileEdge* CatanRoad::GetEdge() const
{
    return edge;
}

void CatanRoad::Move(CatanTileEdge *edge)
{
    this->edge = edge;
}
