#include "texrenderable.h"

TexturedRenderable::TexturedRenderable(QObject *parent) :
    Renderable(parent), geom(new TexGeometry())
{
}

TexturedRenderable::~TexturedRenderable()
{
    qDeleteAll(parts);
    delete geom;
}
