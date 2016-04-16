/****************************************************************************
** **Settlers of Catan**
** Development Card Enumeration
** author: Team Bronies
** date: 4/25/2012
**
** This enumerates the two states of a user object.  If a user has a valid
** TcpSocket connection that is open, then their state is connected,
** otherwise they are DISCONNECTED.
****************************************************************************/

#ifndef USERSTATE_H
#define USERSTATE_H

namespace USER_STATE {

enum ENUM
{
    CONNECTED,
    DISCONNECTED
};

} //namespace USER_STATE

#endif // USERSTATE_H
