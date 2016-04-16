#include "piece.h"

#include "shared/base_player.h"

CatanPiece::CatanPiece(CatanPlayerBase *owner) :
    Entity(owner), owner(owner)
{
}

CatanPlayerBase *CatanPiece::GetOwner() const
{
    return owner;
}
