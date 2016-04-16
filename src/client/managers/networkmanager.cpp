#include "client/managers/networkmanager.h"
#include "shared/managers/sh_networkmanager.h"

ClientConnection* net::Connection = 0;

void net::Send()
{
    Q_ASSERT(net::Connection);
    NetworkManager::getInstance()->Send(net::Connection);
}
