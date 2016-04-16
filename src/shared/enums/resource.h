/****************************************************************************
** **Settlers of Catan**
** Resource Enumeration
** author: Frank Sasto / Dore Weber
** date: 3/27/2012
**
** The RESOURCE enumeration represents the 5 different resources in the
** game.
****************************************************************************/

#ifndef RESOURCE_H
#define RESOURCE_H

#include <QString>

namespace RESOURCE {

enum ENUM { //types of resources
    BRICK,
    WOOL,
    ORE,
    GRAIN,
    LUMBER
};

//returns the display name of the given enumeration
extern QString toString( const ENUM &e );

} //namespace RESOURCE

#endif // RESOURCE_H
