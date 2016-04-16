#ifndef PIECE_H
#define PIECE_H

#include "base.h"

class CatanPlayerBase;

class CatanPiece : public Entity
{
    Q_OBJECT
public:
    explicit CatanPiece(CatanPlayerBase *owner);
    CatanPlayerBase* GetOwner() const;
signals:
    
public slots:
private:
    CatanPlayerBase *owner;
};

#endif // PIECE_H
