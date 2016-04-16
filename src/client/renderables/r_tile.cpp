#include "r_tile.h"
#include "r_chit.h"
#include "shared/entities/tile.h"
#include "client/unitconvert.h"
#include "client/util.h"

static const qreal tile_depth = 0.06;
static const qreal chit_depth = 0.06*0.3;

RenderableTile::RenderableTile(CatanTile *model)
    : TexturedRenderable(model)
{
    this->texture = Texture::getTexture( model->GetType() );
    SetPos(UnitConvert::TileToWorld(model->GetX(), model->GetY()));
    SetAngles(QVector3D(0.0, model->GetYaw(), 0.0));
    if( model->GetTokenValue() )
    {
        chit = new RenderableChit(this, model->GetTokenValue());
        chit->SetPos(QVector3D(0,0,chit_depth));
        chit->SetAngles(QVector3D(0, qrand()%360, 0));
    }
    else
    {
        chit = 0;
    }
    buildGeometry();
}

void RenderableTile::buildGeometry()
{
    Hexagon body(geom, CTILE_SIZE, tile_depth);

    parts << body.parts;

    geom->finalize();
}

void RenderableTile::draw() const
{
    geom->loadArrays();
    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    for (int i = 0; i < parts.count(); ++i)
        parts[i]->draw();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    if( chit )
        chit->Draw();
}
