/****************************************************************************
** **Settlers of Catan**
** Development Card Enumeration
** author: Sarah Hong
** date: 4/7/2012
**
** The DEVELOPMENT CARD enumeration represents the types of development cards
** are in the game.  There are Knight cards, progress, and victory
** points.
****************************************************************************/

#ifndef DEVELOPMENT_H
#define DEVELOPMENT_H

#include <QString>

namespace DEVELOPMENT {

enum ENUM { //types of development cards
    KNIGHT,         //there should be 14 of these in a deck
    MONOPOLY,       //there should be 2 of these in a deck
    YEAR_OF_PLENTY, //there should be 2 of these in a deck
    ROAD_BUILDING,  //there should be 2 of these in a deck
    VICTORY         //there should be 5 of these in a deck
};

//returns the display name of the given enumeration
extern QString toString( const ENUM &e );

} //namespace DEVELOPMENT

#endif // DEVELOPMENT_H
