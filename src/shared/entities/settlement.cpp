#include "settlement.h"
#include "vertex.h"
#include "shared/base_player.h"

CatanSettlement::CatanSettlement(CatanPlayerBase *owner) :
    CatanPiece(owner), vert(0), isCity(false)
{
}

bool CatanSettlement::IsCity() const
{
    return isCity;
}

CatanTileVertex* CatanSettlement::GetVertex() const
{
    return vert;
}

void CatanSettlement::Move(CatanTileVertex *vert)
{
    this->vert = vert;
}
