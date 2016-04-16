#include "gameconfig.h"
#include "shared/defines.h"

CatanGameConfiguration::CatanGameConfiguration(QObject *parent) :
    QObject(parent)
{
    maxPlayers = CATAN_MIN_PLAYERS;
}

int CatanGameConfiguration::GetMaxPlayers() const
{
    return maxPlayers;
}

bool CatanGameConfiguration::GetRandomChits() const
{
    return randomChits;
}

bool CatanGameConfiguration::GetMaritimeTrading() const
{
    return maritimeTrade;
}

void CatanGameConfiguration::SetMaxPlayers(int max)
{
    maxPlayers = qMax( qMin( max, CATAN_MAX_PLAYERS ), CATAN_MIN_PLAYERS );
}

void CatanGameConfiguration::SetRandomChits(bool enabled)
{
    randomChits = enabled;
}

void CatanGameConfiguration::SetMaritimeTrading(bool enabled)
{
    maritimeTrade = enabled;
}
