/****************************************************************************
** **Settlers of Catan**
** CatanChit Entity Class
** author: Frank Sasto / Dore Weber
** date: 3/27/2012
**
** A chit sits on top of CatanTile whose terrain is a resource type.
** Each chit has a number between 2 and 12 excluding 7.  On a player's turn
** when two dice are rolled, the chit is used to determine which resources
** are distributed based on the dice roll.
****************************************************************************/

#ifndef CHIT_H
#define CHIT_H

#include "shared/entities/base.h"

class TexPatch;
struct TexGeometry;

/**
 * Generates the chits that are placed
 * atop the terrain tiles.
 **/
class CatanChit : public Entity
{
public:
    CatanChit();
    ~CatanChit();  //deletes the CatanChit

    /**
     * Sets the value of the chits
     * @param int value
     **/
    void SetValue(int value);

private:

    int value;  //value of the chit
};

#endif // CHIT_H
