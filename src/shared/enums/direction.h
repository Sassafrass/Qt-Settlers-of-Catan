/****************************************************************************
** **Settlers of Catan**
** Direction Enumeration
** author: Frank Sasto / Dore Weber
** date: 3/27/2012
**
** The DIRECTION enumeration represents the 6 cardinal directions of a
** hexagonal grid.  The world of Catan is modeled by a vertically oriented
** hex grid.
****************************************************************************/

#ifndef DIRECTION_H
#define DIRECTION_H

namespace DIRECTION {

enum ENUM { //The hexagonal directions
    UP, //up
    DN, //down
    LL, //lower left
    UL, //upper left
    LR, //lower right
    UR  //upper right
};

}//namespace DIRECTION

#endif // DIRECTION_H
