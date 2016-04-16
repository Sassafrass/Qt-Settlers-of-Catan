/****************************************************************************
** **Settlers of Catan**
** ResCard Class
** author: Sarah Hong
** date: 4/17/2012
**
** Represents the resource cards in a game.  There are 5 different
** types of resources:  lumber, brick, grain, ore, and wool.
****************************************************************************/

#ifndef RESCARD_H
#define RESCARD_H

#include <QObject>
#include "enums/resource.h"

class ResCard : public QObject
{
    Q_OBJECT
public:
    /**
      * Constructor to create a resource card
      */
    explicit ResCard(RESOURCE::ENUM type, QObject *parent = 0);

    /**
      * Returns what the card type is for this resource card.
      */
    RESOURCE::ENUM GetCardType() const;

    
signals:
    
public slots:

protected:
    //the type of the card; lumber, brick, grain, ore, wool
    RESOURCE::ENUM resCardType;
    
};

#endif // RESCARD_H
