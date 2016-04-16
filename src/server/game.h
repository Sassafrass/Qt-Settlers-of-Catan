/****************************************************************************
** **Settlers of Catan**
** Development Card Enumeration
** author: Team Bronies
** date: 4/25/2012
**
** The CatanGame class is responsible for all of the game logic of a
** multiplayer catan game.  It acts as a server for a room of players.
** CatanGame objects are created by the GameManager
****************************************************************************/

#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QVector>
#include "shared/enums/gamestate.h"

class CatanPlayer;
class GameManager;
class TurnManager;
class CatanBoard;
class CatanGameConfiguration;

typedef quint16 GameID;

class CatanGame : public QObject
{
    Q_OBJECT
public:
    explicit CatanGame(GameManager *manager, GameID ID,
                       const QVector<CatanPlayer*>& players,
                       CatanGameConfiguration *config);
    virtual ~CatanGame();
    GameID GetID() const;
    GAME_STATE::ENUM GetState() const;
    const QVector<CatanPlayer*>* GetPlayers() const;
signals:
    void destroying();
public slots:
private slots:
    void beginSetup();
    void endSetup();
    void phasePayout( int roll );
    void phaseRobber();
private: //variables
    GameManager *manager;
    GameID ID;
    QVector<CatanPlayer*> players;
    CatanGameConfiguration *config;
    TurnManager *turnManager;
    CatanBoard *board;
    GAME_STATE::ENUM state;
private: //methods
    void setState(GAME_STATE::ENUM);
    void assignColors();
};

#endif // GAME_H
