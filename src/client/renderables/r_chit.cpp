#include "r_chit.h"
#include "client/unitconvert.h"

static const qreal chit_depth = 0.06*0.3;

RenderableChit::RenderableChit(QObject *parent, int value) :
    TexturedRenderable(parent)
{
    texture = Texture::getTexture(TOKEN::ToEnum(value));
    buildGeometry();
}

void RenderableChit::buildGeometry()
{
    Cylinder body(geom, CTILE_SIZE*0.3, 60, chit_depth);

    parts << body.parts;

    geom->finalize();
}

void RenderableChit::draw() const
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
}
