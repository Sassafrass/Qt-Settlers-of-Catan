/****************************************************************************
** **Settlers of Catan**
** CatanPlayerClass
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** This a class CatanPlayer which inherits from CatanPlayerBase
** This is used in the lobby and game and is used to store important information
** that is needed for the player to hold.
**
****************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include "shared/base_player.h"

class CatanPlayer : public CatanPlayerBase
{
    Q_OBJECT
public:
    static CatanPlayer *localPlayer;
    explicit CatanPlayer(int ID, QString name, QObject *parent = 0);

private:

signals:
    
public slots:
    
};

extern CatanPlayer* LocalPlayer();

#endif // PLAYER_H
