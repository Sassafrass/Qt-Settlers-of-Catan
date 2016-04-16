#ifndef R_PIECE_H
#define R_PIECE_H

#include <QColor>
#include "renderable.h"
#include "geometry/geometry.h"

class CatanPlayerBase;

class RenderablePiece : public Renderable
{
    Q_OBJECT
public:
    explicit RenderablePiece(CatanPlayerBase *owner);
signals:
public slots:
protected:
    QList<Patch *> parts;  //parts of the geometry
    Geometry *geom;  //geometry
    QColor color;
    
};

#endif // R_PIECE_H
