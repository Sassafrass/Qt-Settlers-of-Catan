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

#include "shared/entities/chit.h"
#include "shared/enums/token.h"

CatanChit::CatanChit()
{
}

CatanChit::~CatanChit()
{
}

void CatanChit::SetValue(int value)
{
    this->value = value;
}
