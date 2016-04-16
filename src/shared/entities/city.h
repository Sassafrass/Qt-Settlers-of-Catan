#ifndef CITY_H
#define CITY_H

#include "settlement.h"

class CatanTileVertex;
class CatanPlayerBase;

class CatanCity : public CatanSettlement
{
    Q_OBJECT
public:
    explicit CatanCity(CatanPlayerBase *owner);
    
signals:
    
public slots:
    
};

#endif // CITY_H
