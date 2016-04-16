/****************************************************************************
** **Settlers of Catan**
** Dice Class
** author: Sarah Hong
** date: 4/7/2012
**
** The dice for a game.  There are two methods:  one returns the roll for
** the initial ordering, and the other returns the roll for a regular turn.
** Roll values are determined by the Mersenne algorithm using the current system
** time as the seed to give a random value for each roll.
****************************************************************************/

#ifndef DICE_H
#define DICE_H

#include <QObject>

class Dice : public QObject
{
    Q_OBJECT
public:
    /**
      * Nothing needs to be done in the constructor.
      */
    explicit Dice(QObject *parent = 0);

    /**
      * Returns the next roll for a regular turn.
      */
    int GetRoll();

    /**
      * Returns the initial roll to determine order.
      */
    int GetOrderRoll();
};

#endif // DICE_H
