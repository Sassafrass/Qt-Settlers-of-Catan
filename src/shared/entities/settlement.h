#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include "piece.h"

class CatanTileVertex;
class CatanPlayerBase;

class CatanSettlement : public CatanPiece
{
    Q_OBJECT
public:
    explicit CatanSettlement(CatanPlayerBase *owner);
    bool IsCity() const;
    CatanTileVertex* GetVertex() const;
    void Move( CatanTileVertex *vert );
signals:
public slots:
protected:
    bool isCity;
private:
    CatanTileVertex *vert;
};

#endif // SETTLEMENT_H
