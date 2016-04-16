/****************************************************************************
** **Settlers of Catan**
** Deck Class
** author: Sarah Hong
** date: 4/16/2012
**
** The Deck class is used to represent a deck in the game.  It will only
** contain the development cards since our representation of Catan has an
** unlimited amount of resource cards available in the deck.  A development
** deck will have the following amounts of each card:
**       14 Knight cards
**       6 Progress cards
**       5 Victory Point cards.
** There a different enumerations for each type of Progress card where there
** will be 2 of each type of enumeration.
****************************************************************************/

#ifndef DECK_H
#define DECK_H

#include <QObject>
#include <algorithm>
#include "time.h"
#include "devcard.h"

class Deck : public QObject
{
    Q_OBJECT
public:
    explicit Deck(QObject *parent = 0);

    /**
      * Shuffles the deck using the random_shuffle algorithm to shuffle the cards in the deck.
      */
    void ShuffleDeck();

    /**
      * Draw a card from the deck.
      * Returns:  the next card from the top of the deck.
      */
    DevCard* DrawCard();

private:
    //the list of the cards in the deck
    QList<DevCard*> deck;
    
signals:
    
public slots:
    
};

#endif // DECK_H
