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

#include "client/enums/c_playercolor.h"

extern const QColor PLAYER_COLOR::COLOR_RED = QColor( 255, 0, 0 );
extern const QColor PLAYER_COLOR::COLOR_BLUE = QColor( 0, 0, 255 );
extern const QColor PLAYER_COLOR::COLOR_GREEN = QColor( 0, 255, 0 );
extern const QColor PLAYER_COLOR::COLOR_ORANGE = QColor( 255, 140, 0 );
extern const QColor PLAYER_COLOR::COLOR_WHITE = QColor( 255, 255, 255 );
extern const QColor PLAYER_COLOR::COLOR_BROWN = QColor( 139, 69, 19 );
extern const QColor PLAYER_COLOR::COLOR_NONE = QColor( 0, 0, 0 );

extern QColor PLAYER_COLOR::toColor( const ENUM &e )
{
    switch(e)
    {
    case RED:
        return PLAYER_COLOR::COLOR_RED;
    case BLUE:
        return PLAYER_COLOR::COLOR_BLUE;
    case GREEN:
        return PLAYER_COLOR::COLOR_GREEN;
    case ORANGE:
        return PLAYER_COLOR::COLOR_ORANGE;
    case WHITE:
        return PLAYER_COLOR::COLOR_WHITE;
    case BROWN:
        return PLAYER_COLOR::COLOR_BROWN;
    default:
        return PLAYER_COLOR::COLOR_NONE;
    }
}
