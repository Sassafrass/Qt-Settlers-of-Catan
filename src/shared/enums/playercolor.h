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

#ifndef PLAYERCOLOR_H
#define PLAYERCOLOR_H

#include <QString>

namespace PLAYER_COLOR {

enum ENUM {
    RED,
    BLUE,
    GREEN,
    ORANGE,
    WHITE,
    BROWN,
    NONE
};

//Returns the string equivalent of the color enum
extern QString toString( const ENUM &e );

} //namespace PLAYER_COLOR
typedef PLAYER_COLOR::ENUM PlayerColor;

#endif // PLAYERCOLOR_H
