/****************************************************************************
** **Settlers of Catan**
** Terrain Enumeration
** author: Frank Sasto / Dore Weber
** date: 3/27/2012
**
** The TERRAIN enumeration represents the many different types of tiles
** which represent the world.  Terrain can be land or water.  Each land
** tile represents either a resource or the desert.  Water tiles border
** the world and have ports for maritime trading.
****************************************************************************/

#ifndef TERRAIN_H
#define TERRAIN_H

#include "shared/enums/resource.h"

namespace TERRAIN {

enum ENUM { //different types of terrain
    HILLS,
    PASTURE,
    MOUNTAINS,
    FIELDS,
    FOREST,
    DESERT,
    WATER,
    WATER_ANY,
    WATER_WOOL,
    WATER_BRICK,
    WATER_WHEAT,
    WATER_WOOD,
    WATER_ORE
};

//returns true if the terrain type should have a chit
extern bool HasChit(const ENUM &e);
extern RESOURCE::ENUM ToResource(const ENUM &e);

} //namespace TERRAIN

#endif // TERRAIN_H
