/****************************************************************************
** **Settlers of Catan**
** CatanGame
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** CatanGame is used so that we can keep track of game logic it is also used to
** create the board. It has little to no use at the currrent moment besides to make the game.
**
****************************************************************************/

#ifndef C_CATANGAME_H
#define C_CATANGAME_H

#include <QObject>

class CatanGame : public QObject
{
    Q_OBJECT
public:
    explicit CatanGame(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // C_CATANGAME_H
