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

#include "shared/enums/terrain.h"

extern bool TERRAIN::HasChit(const ENUM &e)
{
    return (e != DESERT && e != WATER &&
            e != WATER_ANY && e != WATER_WOOL &&
            e != WATER_BRICK && e != WATER_WHEAT &&
            e != WATER_WOOD && e != WATER_ORE);
}

extern RESOURCE::ENUM TERRAIN::ToResource(const ENUM &e)
{
    switch( e )
    {
    case HILLS:
        return RESOURCE::BRICK;
    case PASTURE:
        return RESOURCE::WOOL;
    case MOUNTAINS:
        return RESOURCE::ORE;
    case FIELDS:
        return RESOURCE::GRAIN;
    default:
        return RESOURCE::LUMBER;
    }
}
