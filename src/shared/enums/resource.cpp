/****************************************************************************
** **Settlers of Catan**
** Resource Enumeration
** author: Frank Sasto / Dore Weber
** date: 3/27/2012
**
** The RESOURCE enumeration represents the 5 different resources in the
** game.
****************************************************************************/

#include "shared/enums/resource.h"

extern QString RESOURCE::toString( const ENUM &e )
{
    switch(e)
    {
    case BRICK:
        return "Brick";
    case WOOL:
        return "Wool";
    case ORE:
        return "Ore";
    case GRAIN:
        return "Grain";
    case LUMBER:
        return "Lumber";
    default:
        return "Bad Resource";
    }
}
