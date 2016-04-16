/****************************************************************************
** **Settlers of Catan**
** UnitConvert.h
** author: Frank Sasto / Dore Weber
** date: 3/27/2012
**
** This namespace provides utility functions for transforming world-space
** coordinates to a special hexagonal coordinate system made specifically
** for this game.
****************************************************************************/

#ifndef UNITCONVERT_H
#define UNITCONVERT_H

#include "shared/sh_util.h"

static const qreal CTILE_HEIGHT = .5;
static const qreal CTILE_HALF_HEIGHT = CTILE_HEIGHT * 0.5;
static const qreal CTILE_NARROW_WIDTH = CTILE_HEIGHT / qCos( d2r( 30 ) );
static const qreal CTILE_SIZE = CTILE_NARROW_WIDTH * 0.5;
static const qreal CTILE_SEGMENT = CTILE_SIZE * qSin( d2r( 30 ) );
static const qreal CTILE_WIDTH = (3*CTILE_HALF_HEIGHT) / (2*qSin( d2r( 60 ) ));

namespace UnitConvert
{
    QPoint WorldToTile( const QVector3D &worldPos );
    QPoint WorldToTile( const QVector2D &worldPos );
    QPoint WorldToVertex( const QVector3D &worldPos );
    QPoint WorldToVertex( const QVector2D &worldPos );
    QPoint WorldToEdge( const QVector3D &worldPos );
    QPoint WorldToEdge( const QVector2D &worldPos );
    QVector3D EdgeToWorld( const int x, const int y );
    QVector3D VertexToWorld (const int x, const int y );
    QVector3D TileToWorld( const QPoint &pos );
    QVector3D TileToWorld( const int x, const int y );
}

#endif // UNITCONVERT_H
