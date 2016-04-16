/****************************************************************************
** **Settlers of Catan**
** TexturedRenderable
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** This class uses Renderable and make it so that we can turn the board into
** a real borad. this is used in the game screen.
**
****************************************************************************/


#ifndef TEXRENDERABLE_H
#define TEXRENDERABLE_H

#include "renderable.h"
#include "geometry/geometry.h"

class TexturedRenderable : public Renderable
{
    Q_OBJECT
public:
    explicit TexturedRenderable(QObject *parent);
    virtual ~TexturedRenderable();
signals:
    
public slots:
protected:
    QList<TexPatch *> parts;  //parts of the geometry
    TexGeometry *geom;  //texturable geometry
    GLuint texture;      //texture
    
};

#endif // TEXRENDERABLE_H
