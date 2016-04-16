
#include <QVector2D>
#include <QVector3D>
#include "unitconvert.h"

inline int rem(int a, int b)
{
    return a-b*qFloor((qreal)a/b);
}

inline long double rem1(long double a)
{
    return a-qFloor(a);
}

QPoint UnitConvert::WorldToTile( const QVector3D &worldPos )
{
    return WorldToTile( QVector2D( worldPos.x(), worldPos.y() ) );
}

QPoint UnitConvert::WorldToTile( const QVector2D &worldPos )
{
    qreal x = worldPos.x() / CTILE_WIDTH + 0.666666666;
    qreal y = worldPos.y() / CTILE_HEIGHT + 0.5 + qFloor(x) * 0.5;

    qreal a = qAtan2( 0.5 - rem1(y), rem1(x) );
    if( a < -1 )
    {
        x = x - 1;
    }
    else if( a > 1 )
    {
        y = y - 1;
        x = x - 1;
    }
    return QPoint( qFloor(x), qFloor(y) );
}

QPoint UnitConvert::WorldToVertex( const QVector3D &worldPos )
{
    return WorldToVertex( QVector2D( worldPos.x(), worldPos.y() ) );
}

QPoint UnitConvert::WorldToVertex( const QVector2D &worldPos )
{
    qreal u = worldPos.x() / CTILE_WIDTH;
    qreal v = worldPos.y() / CTILE_HALF_HEIGHT + u;

    qreal b = rem1(v / 2.0);

    if( b > rem1(u) )
        v = v + 1;

    if( b > 0.5 )
        v = v - 1;

    return QPoint(qFloor(u), qFloor(v));
}

QPoint UnitConvert::WorldToEdge( const QVector3D &worldPos )
{
    return WorldToEdge( QVector2D( worldPos.x(), worldPos.y() ) );
}

QPoint UnitConvert::WorldToEdge( const QVector2D &worldPos )
{
    qreal x = (worldPos.x() - CTILE_SIZE) / CTILE_WIDTH + 0.66666666666;
    qreal y = worldPos.y() / CTILE_HEIGHT * 3 + 1.5 + qFloor(x) * 1.5;

    qreal c = rem1(x);
    qreal b = rem1(y / 3.0);
    if( c < 0.666666666 )
    {
        qreal a = qAtan2( 0.5 - b, c );
        if( a < -1 )
        {
            x = x - 1;
            y = y - 1;
        }
        else if( a > 1 )
        {
            y = y - 2;
            x = x - 1;
        }
        if( b > 0.5 )
            y = y + 2;
    }
    else
    {
        qreal a = qAtan2( 0.5-b, c-0.666666666 );
        if( a < -1 )
            y = y + 1;
        else if( a > 1 )
            y = y - 1;
        y = y + 1;
    }

    return QPoint(qFloor(x), qFloor(y - qFloor(b*3)));
}

QVector3D UnitConvert::EdgeToWorld( const int PosX, const int PosY )
{

    qreal wx = PosX * CTILE_WIDTH;
    qreal wy = (PosY - PosX*1.5 - 1.5) / 3 * CTILE_HEIGHT;

    wx = wx + CTILE_SIZE;

    qreal a = rem(PosY, 3);
    if( a == 0 )
    {
        wx = wx - CTILE_SEGMENT * 0.5;
        wy = wy + CTILE_HALF_HEIGHT * 0.5;
    }
    else if( a == 1 )
    {
        wx = wx + CTILE_SIZE * 0.5;
        wy = wy + CTILE_HALF_HEIGHT - CTILE_HEIGHT * 0.333333333;
    }
    else if( a == 2 )
    {
        wx = wx - CTILE_SEGMENT * 0.5;
        wy = wy + CTILE_HEIGHT * 0.333333333 - CTILE_HALF_HEIGHT * 0.5;
    }

     return QVector3D( wx, wy, 0 );
}

QVector3D UnitConvert::VertexToWorld (const int PosX, const int PosY )
{
    qreal wx = PosX * CTILE_WIDTH;
    qreal wy = (PosY - PosX) * CTILE_HALF_HEIGHT;

    if( rem(PosY, 2) == 0 )
        wx = wx + CTILE_SIZE;
    else
        wx = wx + CTILE_SEGMENT;

    return QVector3D( wx, wy, 0 );

}

QVector3D UnitConvert::TileToWorld( const QPoint &pos )
{
    return TileToWorld( pos.x(), pos.y() );
}

QVector3D UnitConvert::TileToWorld( const int x, const int y )
{
    qreal wx = x * CTILE_WIDTH;
    qreal wy = (2*y - x) * CTILE_HALF_HEIGHT;

    return QVector3D( wx, wy, 0.0 );
}
