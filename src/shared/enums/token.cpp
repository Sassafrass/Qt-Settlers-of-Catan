/****************************************************************************
** **Settlers of Catan**
** Token Enumeration
** author: Frank Sasto / Dore Weber
** date: 3/27/2012
**
** The TOKEN enumeration represents the possible chit numbers.
** Each chit is a number between 2 and 12 excluding 7.
****************************************************************************/

#include "shared/enums/token.h"

extern TOKEN::ENUM TOKEN::ToEnum( int value )
{
    switch(value)
    {
    case 2:
        return TWO;
    case 3:
        return THREE;
    case 4:
        return FOUR;
    case 5:
        return FIVE;
    case 6:
        return SIX;
    case 8:
        return EIGHT;
    case 9:
        return NINE;
    case 10:
        return TEN;
    case 11:
        return ELEVEN;
    case 12:
        return TWELVE;
    default:
        return NONE;
    }
}
