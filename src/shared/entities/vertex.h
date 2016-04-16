#ifndef VERTEX_H
#define VERTEX_H

#include <QList>
#include "shared/entities/socket.h"

class CatanBoard;
class CatanSettlement;
class CatanTile;
class CatanTileEdge;

class CatanTileVertex : public CatanTileSocket
{
    Q_OBJECT
public:
    explicit CatanTileVertex(CatanBoard* board, const QPoint &pos);
    CatanSettlement* GetSettlement() const;
    QList<CatanTile*> GetAdjacentTiles() const;
    QList<CatanTileVertex*> GetAdjacentVertices() const;
    QList<CatanTileEdge*> GetAdjacentEdges() const;
signals:
    
public slots:
private:
};

#endif // VERTEX_H
