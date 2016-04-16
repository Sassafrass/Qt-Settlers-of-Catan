/****************************************************************************
** **Settlers of Catan**
** RenderableTile
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** This tile is renedered by using open GL and is placed into the board object-
** This is a client side object.
**
****************************************************************************/

#ifndef R_TILE_H
#define R_TILE_H

#include "texrenderable.h"

class RenderableChit;
class CatanTile;
class RenderableTile : public TexturedRenderable
{
    Q_OBJECT
public:
    RenderableTile(CatanTile *parent);
protected:
    /**
     * Builds the geometry of the object
     **/
    virtual void buildGeometry();
    /**
     * Draws the geometry of the object
     **/
    virtual void draw() const;
private:
    RenderableChit* chit;
};

#endif // R_TILE_H
