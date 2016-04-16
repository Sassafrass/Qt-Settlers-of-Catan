#include <QTimer>
#include <QDebug>
#include "turnmanager.h"
#include "server/game.h"
#include "shared/entities/board.h"
#include "shared/dice.h"

TurnManager::TurnManager(CatanGame *game, const QVector<CatanPlayer*> &players) :
    QObject(game), game(game), activePlayer(0)
{
    die = new Dice(this);
    rollOrders = new QMap<PlayerID, int>();
    playerCount = players.size();
    turnDirection = Forward;
    currentPhase = TURN_PHASE::ROLL;

    phaseTimer.setSingleShot(true);
    connect( &phaseTimer, SIGNAL(timeout()),
             this, SLOT(advancePhase()));

    foreach( CatanPlayer *player, players )
    {
        connect( player, SIGNAL(rolledDice()),
                 this, SLOT(onRolledDice()));
        player->RollDice();
    }
}

TurnManager::~TurnManager()
{
    if( die )
        delete die;
    if( rollOrders )
        delete rollOrders;
}

CatanPlayer* TurnManager::GetActivePlayer() const
{
    return *activePlayer;
}

void TurnManager::onRolledDice()
{
    CatanPlayer *player = qobject_cast<CatanPlayer*>(sender());
    Q_ASSERT(player);

    //qDebug() << "Player " << player->GetName() << " rolled the die";

    int result = die->GetRoll();

    //if we are determining the turn order
    if( rollOrders )
    {
        //store this player's roll
        QMap<PlayerID, int>& rollRef = *rollOrders;
        rollRef[player->GetID()] = result;

        //loop through the current rolls
        QList<CatanPlayer*>::iterator i;
        for( i = turnOrder.begin();
             i != turnOrder.end(); ++i )
        {
            //get the other player's roll result
            int otherPlayerRoll = rollRef[(*i)->GetID()];

            if( otherPlayerRoll == result )
            {
                //we both rolled the same number, randomly decide who goes before
                if( qrand() % 500 > 250 )
                    break;
            }
            else if( result < otherPlayerRoll )
            {
                //our result is lower, we belong before them
                break;
            }
        }

        //put this player in the turn order
        turnOrder.insert(i, player);

        if( turnOrder.size() == playerCount )
        {
            delete rollOrders;
            rollOrders = 0;
            activePlayer = turnOrder.begin();
            currentPhase = TURN_PHASE::SETUP;
            emit orderDetermined();
        }
    }
    else if( currentPhase == TURN_PHASE::ROLL )
    {
        if( result != 7 )
        {
            currentPhase = TURN_PHASE::PAYOUT;
            emit phasePayout( result );
            phaseTimer.start(3 * 1000);
        }
        else
        {
            currentPhase = TURN_PHASE::ROBBER_PLACEMENT;
            emit phaseRobber();
            phaseTimer.start(7 * 1000);
        }
    }
}

TURN_PHASE::ENUM TurnManager::GetPhase() const
{
    return currentPhase;
}

void TurnManager::advancePhase()
{
    phaseTimer.stop();
    //TODO: goto next phase
}

void TurnManager::nextTurn()
{
    Q_ASSERT( !turnOrder.isEmpty() );

    turnCount++;
    if( turnDirection == Forward )
    {
        //have we reached the end of the list?
        if( activePlayer++ == turnOrder.end() )
        {
            if( game->GetState() == GAME_STATE::SETUP )
            {
                //at the end of the turn order, the last player gets to go
                //twice and the turn order is reversed.
                //let this player go again, but reverse the turn direction
                activePlayer = --turnOrder.end();
                turnDirection = Backward;
            }
            else
            {
                //loop around to the beginning of the list
                activePlayer = turnOrder.begin();
            }
        }
    }
    else
    {
        //have we not reached the beginning of the list?
        if( activePlayer != turnOrder.begin() )
        {
            //keep going toward the beginning
            activePlayer--;
        }
        else
        {
            //we're done
            turnDirection = Forward;
            //signal every player to get a resource card
            //for each tile their settlements occupy.
            emit setupComplete();
        }
    }

    if( game->GetState() == GAME_STATE::STRIFE )
    {
        currentPhase = TURN_PHASE::ROLL;
        GetActivePlayer()->RollDice();
    }
    else if( game->GetState() == GAME_STATE::SETUP )
    {
        //TODO: create a settlement for this player
        //give the player 30 seconds to place their starting piece
        phaseTimer.start(30 * 1000);
    }

}
