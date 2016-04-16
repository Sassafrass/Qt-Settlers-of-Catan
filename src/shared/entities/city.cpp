#include "city.h"
#include "shared/base_player.h"

CatanCity::CatanCity(CatanPlayerBase *owner) :
    CatanSettlement(owner)
{
    isCity = true;
}
