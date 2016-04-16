/****************************************************************************
** **Settlers of Catan**
** net
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** The net is used in all of our code to send and recieve signals
** This is referanced in all classes and is used with the syntax net::
**
****************************************************************************/


#ifndef C_NETWORKMANAGER_H
#define C_NETWORKMANAGER_H

#include "shared/managers/sh_networkmanager.h"
#include "client/client.h"

namespace net {

extern ClientConnection *Connection;
void Send();

} //namespace net

#endif // NETWORKMANAGER_H
