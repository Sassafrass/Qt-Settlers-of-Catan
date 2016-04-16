/****************************************************************************
** **Settlers of Catan**
** Development Card Enumeration
** author: Team Bronies
** date: 4/25/2012
**
** The TURN_PHASE enumeration enumerates all of the possible stages of
** a turn in the game.  Each player has a turn, which starts at the ROLL
** phase, and ends with the BUILD or SPECIAL_BUILD phase.
****************************************************************************/

#ifndef TURNPHASE_H
#define TURNPHASE_H

namespace TURN_PHASE {

enum ENUM
{
    SETUP,
    ROLL,
    PAYOUT,
    ROBBER_PLACEMENT,
    ROBBER_STEAL,
    TRADE,
    BUILD,
    SPECIAL_BUILD
};

} //namespace TURN_PHASE

#endif // TURNPHASE_H
