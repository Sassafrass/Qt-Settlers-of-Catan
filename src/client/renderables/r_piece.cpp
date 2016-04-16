#include "r_piece.h"
#include "shared/base_player.h"
#include "client/enums/c_playercolor.h"
RenderablePiece::RenderablePiece(CatanPlayerBase *owner) :
    Renderable(owner), geom(new Geometry())
{
    color = PLAYER_COLOR::toColor( owner->GetColor() );
}
