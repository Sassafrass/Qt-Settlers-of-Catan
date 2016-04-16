/****************************************************************************
** **Settlers of Catan**
** DevCard Class
** author: Sarah Hong
** date: 4/17/2012
**
** Represents the development cards in a game.  There are 5 different
** types of development cards:  KNIGHT, YEAR OF PLENTY, MONOPOLY,
** ROAD_BUILDING, and VICTORY.
****************************************************************************/

#ifndef DEVCARD_H
#define DEVCARD_H

#include <QObject>
#include "shared/enums/development.h"

class DevCard : public QObject
{
    Q_OBJECT
public:
    /**
      * Constructor to make a development card.
      */
    explicit DevCard(DEVELOPMENT::ENUM type, const QString& inst, QObject *parent = 0);

    /**
      * Returns the type of this development card.
      */
    DEVELOPMENT::ENUM GetCardType() const;

    /**
      * Returns the instructions on this development card.
      */
    QString GetInstructions() const;
    
signals:
    
public slots:
    
protected:
    //the type of the development card as specified in the class header
    DEVELOPMENT::ENUM devCardType;
    //the instructions on the development card
    QString instructions;
    //TODO:  figure out other elements to the development card such as cost, effects, isPlayed, etc.
};

#endif // DEVCARD_H
