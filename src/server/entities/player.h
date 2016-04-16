/****************************************************************************
** **Settlers of Catan**
** Development Card Enumeration
** author: Team Bronies
** date: 4/25/2012
**
** The Player class holds all the state information about a player
** in a Catan game.  The player has a hand of cards, their achievements,
** their passive and active pieces, and a User object.
****************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QDataStream>

#include "shared/enums/command.h"
#include "shared/base_player.h"

class CatanUser;
class CatanPlayer : public CatanPlayerBase
{
    Q_OBJECT
public:
    explicit CatanPlayer(PlayerID ID, CatanUser *user, QObject *parent = 0);
    virtual ~CatanPlayer();
    CatanUser* GetUser() const;
signals:
    void destroying(); //emitted in the destructor
    void receivedCommand(NetworkCommand cmd, QDataStream&); //when the client of this player sent us a command
    void requestChangeConfig(QDataStream&); //when this player changes a config option
    void requestLeaveRoom(); //when this player's user has requested to leave the room
    void requestStartGame(); //when this player's user has requested to start the game
    void readyUp(bool); //when this player's user has toggle his/her ready status
    void rolledDice(); //when this player has rolled the dice.
public slots:
    void RollDice(); //orders this player to roll the dice
private slots:
    void onReceivedCommand(NetworkCommand cmd, QDataStream&); //when the client of this player sent us a command
private:
    CatanUser *user;
};

#endif // PLAYER_H
