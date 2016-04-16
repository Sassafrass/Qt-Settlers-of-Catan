/****************************************************************************
** **Settlers of Catan**
** Hand Class
** author: Sarah Hong
** date: 4/7/2012
**
** Represents the player's hand and the cards the player has.
****************************************************************************/

#ifndef HAND_H
#define HAND_H

#include <QObject>
#include <QMap>
#include "devcard.h"
#include "shared/enums/resource.h"

class CatanPlayerBase;

class PlayerHand : public QObject
{
    Q_OBJECT
public:
    /**
      * Constructor, gives everyone their initial resources
      */
    explicit PlayerHand(CatanPlayerBase *owner);

    /**
      * Called when a player uses a resource card from their hand. First confirms if the request is valid.
      * If it is not valid, then it will terminate early and not perform any removals.
      *
      * Param:  QMap<RESOURCE::ENUM, int> resources - the resources along with how many to remove from the hand.
      * Return: true if the request is valid, false if the request is bad.
      */
    bool UseResources(QMap<RESOURCE::ENUM, int> resources);

    /**
      * Called when the UseResources driver has confirmed that the request to remove cards from
      * the player's hand is valid.
      *
      * Return:  true if the removal is successful, false if something went wrong.
      */
    bool UseResource(RESOURCE::ENUM resource, int count );

    /**
      * Called when the player uses a development card from their hand.
      *
      * Param:  DEVELOPMENT::ENUM type - the type of the development card the player wants
      *                                  to play from their hand.
      */
    bool PlayDevelopment(DEVELOPMENT::ENUM type);

    /**
      * Called when the player has a resource card that should be added to their hand.
      * Param: QList<RESOURCE::ENUM> cards - the resources to give to this player.
      */
    void AddResource(QList<RESOURCE::ENUM> cards);
    void AddResource(RESOURCE::ENUM res, int count=1);

    /**
      * Called when the player has purchased a development card.
      * Param: DevCard* card - the new card to be added.
      */
    void AddDevCardToHand(DevCard* card);

    /**
      * Returns the number of cards for a particular resource.
      */
    int GetResCount(RESOURCE::ENUM type);

    /**
      * Returns the number of cards for a particular development card.
      */
    int GetDevCount(DEVELOPMENT::ENUM type);

signals:

public slots:

protected:
    //list of the development cards in the player's hand
    QList<DevCard*> devHand;

    //keeps track of the counts for the resources in a player's hand
    QMap<RESOURCE::ENUM, int> resourceCounts;
    //keeps track of the counts for the development cards in a player's hand
    QMap<DEVELOPMENT::ENUM, int> developmentCounts;

    //the owner of this deck
    CatanPlayerBase *owner;
};

#endif // HAND_H
