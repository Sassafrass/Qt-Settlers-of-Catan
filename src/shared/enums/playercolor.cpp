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

#include "shared/enums/playercolor.h"

extern QString PLAYER_COLOR::toString( const PlayerColor &e )
{
    switch(e)
    {
    case RED:
        return "Red";
    case BLUE:
        return "Blue";
    case GREEN:
        return "Green";
    case ORANGE:
        return "Orange";
    case WHITE:
        return "White";
    case BROWN:
        return "Brown";
    default:
        return "Colorless";
    }
}
