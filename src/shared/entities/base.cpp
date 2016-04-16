/****************************************************************************
** **Settlers of Catan**
** Base Entity Class
** author: Frank Sasto / Dore Weber
** date: 3/27/2012
**
** This is the base entity class for all drawable entities.
** An entity has a position and angle in world space coordinates.
****************************************************************************/

#include "shared/entities/base.h"
#include "shared/sh_util.h"

Entity::Entity(QObject *parent) :
    QObject(parent)
{
    parentEnt = 0;
}

void Entity::SetParent(Entity &parent)
{
    parentEnt = &parent;
}

Entity* Entity::GetParent()
{
    return parentEnt;
}
