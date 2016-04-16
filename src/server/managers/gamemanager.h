/****************************************************************************
** **Settlers of Catan**
** Development Card Enumeration
** author: Team Bronies
** date: 4/25/2012
**
** The GameManager class is reponsible for creating and managing Catan games
****************************************************************************/

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QMap>

#include "server/managers/networkmanager.h"
#include "server/game.h"

class CatanUser;
class CatanServer;
class CatanGameConfiguration;

class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(CatanServer *server);
    void CreateGame( CatanGameConfiguration *config,
                     const QVector<CatanPlayer*>& players );
    CatanGame* GetByID( GameID ID ) const;
    CatanServer* GetServer() const;
signals:
public slots:
private slots:
    void onGameDestroyed();
private:
    CatanServer *server;
    QMap< GameID, CatanGame* > games;
    int gameIDCounter; //increments to give each game a unique 	ID number
};

#endif // GAMEMANAGER_H
