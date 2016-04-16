#include "player.h"

CatanPlayer* CatanPlayer::localPlayer = 0;
extern CatanPlayer* LocalPlayer()
{
    return CatanPlayer::localPlayer;
}

CatanPlayer::CatanPlayer(int ID, QString name, QObject *parent) :
    CatanPlayerBase(ID, parent)
{
    this->name = name;
    color = PLAYER_COLOR::NONE;
}
