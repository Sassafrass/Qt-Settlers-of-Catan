#include "server/managers/networkmanager.h"
#include "shared/connection.h"
#include "shared/qout.h"
#include "server/user.h"
#include "server/entities/player.h"

#include "shared/managers/sh_networkmanager.cpp"

void net::Send(const QList<Connection*> &rf)
{
    NetworkManager::getInstance()->Send(rf);
}

void net::Send(const QList<CatanUser*> &users)
{
    QList<Connection*> receipientFilter;
    foreach( CatanUser* user, users )
    {
        if( user->GetConnection() )
            receipientFilter.push_back((Connection*)(user->GetConnection()));
    }

    NetworkManager::getInstance()->Send(receipientFilter);
}

void net::Send(const QVector<CatanPlayer*> &players)
{
    QList<Connection*> receipientFilter;
    foreach( CatanPlayer* player, players )
    {
        if( player->GetUser()->GetConnection() )
            receipientFilter.push_back((Connection*)(player->GetUser()->GetConnection()));
    }

    NetworkManager::getInstance()->Send(receipientFilter);
}

void net::Send(CatanUser* user)
{
    NetworkManager::getInstance()->Send((Connection*)user->GetConnection());
}

void net::Send(Connection* conn)
{
    NetworkManager::getInstance()->Send(conn);
}
