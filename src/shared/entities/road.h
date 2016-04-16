#ifndef ROAD_H
#define ROAD_H

#include "piece.h"

class CatanTileEdge;
class CatanPlayerBase;

class CatanRoad : public CatanPiece
{
    Q_OBJECT
public:
    explicit CatanRoad(CatanPlayerBase *owner);
    CatanTileEdge* GetEdge() const;
    void Move( CatanTileEdge *edge );
signals:
public slots:
protected:
private:
    CatanTileEdge *edge;
};

#endif // SETTLEMENT_H
