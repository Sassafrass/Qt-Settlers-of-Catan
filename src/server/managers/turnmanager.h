/****************************************************************************
** **Settlers of Catan**
** Development Card Enumeration
** author: Team Bronies
** date: 4/25/2012
**
** The TurnManager manages a player's turn in the game.  It is responsible
** for counting down between each turn phase and advancing to the next
** phase.  When the final phase is complete, the next player's turn begins
****************************************************************************/

#ifndef TURNMANAGER_H
#define TURNMANAGER_H

#include <QObject>
#include <QVector>
#include <QMap>
#include <QTimer>
#include "shared/enums/turnphase.h"
#include "server/entities/player.h"

class CatanGame;
class CatanBoard;
class Dice;

class TurnManager : public QObject
{
    enum TurnOrder { //think clockwise/counter-clockwise around the table.
        Forward,
        Backward
    };

    Q_OBJECT
public:
    explicit TurnManager(CatanGame *game, const QVector<CatanPlayer*>& players);
    virtual ~TurnManager();
    CatanPlayer* GetActivePlayer() const;
    TURN_PHASE::ENUM GetPhase() const;
signals:
    void orderDetermined();
    void setupComplete();
    void phasePayout(int roll);
    void phaseRobber();
public slots:
private slots:
    void onRolledDice();
    void advancePhase();
private: //variables
    CatanGame *game;
    QList<CatanPlayer*>::iterator activePlayer;
    TURN_PHASE::ENUM currentPhase;
    QTimer phaseTimer;
    Dice *die;
    QMap<PlayerID, int> *rollOrders;
    QList<CatanPlayer*> turnOrder;
    int playerCount;
    int turnCount;
    TurnOrder turnDirection;
private: //methods
    void nextTurn();

};

#endif // TURNMANAGER_H
