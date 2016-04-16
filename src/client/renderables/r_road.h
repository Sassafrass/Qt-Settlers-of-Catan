/****************************************************************************
** **Settlers of Catan**
** RenderableChit
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** This is used so that we will be able to draw the chit on top of the
** tile this is used just on top of the tile object and is only used on the client side
**
****************************************************************************/

#ifndef R_ROAD_H
#define R_ROAD_H

#include "r_piece.h"

class CatanPlayerBase;

class RenderableRoad : public RenderablePiece
{
    Q_OBJECT
public:
    explicit RenderableRoad(CatanPlayerBase *owner);
    
signals:

public slots:
protected:
    /**
     * Builds the geometry of the object
     **/
    virtual void buildGeometry();
    /**
     * Draws the geometry of the object
     **/
    virtual void draw() const;
    
};

#endif // R_ROAD_H
