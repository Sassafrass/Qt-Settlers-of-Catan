#include "r_road.h"
#include "client/unitconvert.h"
#include "shared/base_player.h"

static const qreal chit_depth = 0.06*0.3;

RenderableRoad::RenderableRoad(CatanPlayerBase *owner) :
    RenderablePiece(owner)
{
    buildGeometry();
}

void RenderableRoad::buildGeometry()
{
    RectPrism body(geom, CTILE_SIZE * 0.6, CTILE_SIZE * 0.08, CTILE_SIZE * 0.08 );

    parts << body.parts;

    geom->finalize();

    //set the geometry's color
    for (int i = 0; i < parts.count(); ++i)
        qSetColor(parts[i]->faceColor, color);
}

void RenderableRoad::draw() const
{

    geom->loadArrays();
    //glBindTexture(GL_TEXTURE_2D, texture);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    for (int i = 0; i < parts.count(); ++i)
        parts[i]->draw();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}
