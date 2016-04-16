/****************************************************************************
** **Settlers of Catan**
** util.h
** author: Frank Sasto / Dore Weber
** date: 3/27/2012
**
** This namespace provides utility functions for math operations such as
** matrix multiplication and degrees to radians
****************************************************************************/

#ifndef SH_UTIL_H
#define SH_UTIL_H

#include <qmath.h>

inline qreal d2r( qreal deg )
{
    return deg * M_PI / 180;
}

#endif // SH_UTIL_H
