#include "board.h"
#include "socket.h"

CatanTileSocket::CatanTileSocket(CatanBoard *board, const QPoint &pos, int yaw) :
    Entity(board), pos(pos), yaw(yaw), board(board), piece(0)
{
}

QPoint CatanTileSocket::GetPos() const
{
    return pos;
}

int CatanTileSocket::GetX() const
{
    return pos.x();
}

int CatanTileSocket::GetY() const
{
    return pos.y();
}

int CatanTileSocket::GetYaw() const
{
    return yaw;
}

CatanPiece* CatanTileSocket::GetPiece() const
{
    return piece;
}

void CatanTileSocket::SetPiece( CatanPiece *p )
{
    piece = p;
}
