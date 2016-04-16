/****************************************************************************
** **Settlers of Catan**
** Development Card Enumeration
** author: Team Bronies
** date: 4/25/2012
**
** The NetworkManager is actually a network interface for making sending
** messages between the client and the server easier to maintain.
** The goal is to create an abstract and easy way to start and commit
** a message to a TcpSocket connection.
****************************************************************************/

#ifndef S_NETWORKMANAGER_H
#define S_NETWORKMANAGER_H

#include <QObject>
#include <QVector>
#include "shared/enums/command.h"
#include "shared/managers/sh_networkmanager.h"

class Connection;
class CatanPlayer;
class CatanUser;

namespace net {

void Send(const QList<CatanUser*> &rf);
void Send(const QVector<CatanPlayer*> &rf);
void Send(const QList<Connection*> &rf);
void Send(Connection* conn);
void Send(CatanUser* user);

} //namespace net

#endif // S_NETWORKMANAGER_H
