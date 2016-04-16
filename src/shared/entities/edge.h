#ifndef EDGE_H
#define EDGE_H

#include <QList>
#include "shared/entities/socket.h"

class CatanBoard;
class CatanRoad;
class CatanTile;
class CatanTileVertex;

class CatanTileEdge : public CatanTileSocket
{
    Q_OBJECT
public:
    explicit CatanTileEdge(CatanBoard* board, const QPoint &pos);
    CatanRoad* GetRoad() const;
    QList<CatanTile*> GetAdjacentTiles() const;
    QList<CatanTileVertex*> GetAdjacentVertices() const;
    QList<CatanTileEdge*> GetAdjacentEdges() const;
signals:
    
public slots:
private:
};

#endif // EDGE_H
