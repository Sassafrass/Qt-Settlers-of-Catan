/****************************************************************************
** **Settlers of Catan**
** Player Color Enumeration
** author: Frank Sasto / Dore Weber
** date: 3/27/2012
**
** The PLAYER_COLOR enumeration represents the 6 available colors a player
** of Catan can choose.  Each color represents an empire in the world of
** Catan.
****************************************************************************/

#ifndef C_PLAYERCOLOR_H
#define C_PLAYERCOLOR_H

#include <QColor>
#include "shared/enums/playercolor.h"

namespace PLAYER_COLOR {

extern const QColor COLOR_RED;
extern const QColor COLOR_BLUE;
extern const QColor COLOR_GREEN;
extern const QColor COLOR_ORANGE;
extern const QColor COLOR_WHITE;
extern const QColor COLOR_BROWN;
extern const QColor COLOR_NONE;

//Returns the color equivalent of the color enum
extern QColor toColor( const PlayerColor &e );

} //namespace PLAYER_COLOR

#endif // C_PLAYERCOLOR_H
