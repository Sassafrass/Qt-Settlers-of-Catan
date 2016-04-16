#ifndef SOCKET_H
#define SOCKET_H

#include <QList>
#include <QPoint>
#include "shared/entities/base.h"

class CatanBoard;
class CatanPiece;
class CatanTile;

class CatanTileSocket : public Entity
{
    Q_OBJECT
public:
    explicit CatanTileSocket(CatanBoard* board, const QPoint& pos, int yaw);
    CatanPiece* GetPiece() const;
    void SetPiece(CatanPiece*);
    QPoint GetPos() const;
    int GetX() const;
    int GetY() const;
    int GetYaw() const;
signals:
    
public slots:
protected:
    QPoint pos;
    int yaw;
    CatanBoard *board;
    CatanPiece *piece;
};

#endif // SOCKET_H
