/****************************************************************************
** **Settlers of Catan**
** ScreenGameLobby
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** From: ScreenJoin, ScreenCreate To: GameBoard, JoinCreateScreen
** This is the game lobby it is one of our largest screens. This screen has evenHandlers
** that have slots to run it.
** This class can move to game board when all players have readied up.
** If you Leave using the exit button you will take you to the JoinCreateScreen.
** TODO:
** need to make the colors work as I would like
**
****************************************************************************/

#ifndef SCREENGAMELOBBY_H
#define SCREENGAMELOBBY_H

#include <QWidget>
#include <QList>
#include <QMap>
#include <QTime>

#include "client/screens/catanscreen.h"

class CatanPlayer;
class PlayerReadyWidget;
namespace Ui {
class ScreenGameLobby;
}

class ScreenGameLobby : public CatanScreen
{
    Q_OBJECT
    
public:
    explicit ScreenGameLobby(QWidget *parent, ScreenManager *manager, const QPoint &pos);
    QVector<CatanPlayer *> GetPlayerVector();
    ~ScreenGameLobby();
private slots:
    void receivedRoomPlayers(QDataStream&);
    void receivedRoomUserJoined(QDataStream&);
    void receivedRoomUserExited(QDataStream&);
    void receivedRoomNewHost(QDataStream&);
    void receivedRoomPlayerReady(QDataStream&);
    void receivedRoomStart(QDataStream &);
    void receivedRoomStarting();
    void receivedRoomStartingInterrupt(QDataStream&);
    void sendStartGame();
    void cancelButtonPressed();
    void exitButtonPressed();
    void updateTimer();
protected:
    virtual void Activated();
    virtual void Deactivated();
private:
    void moveToGameBoard();
    void everyoneReady();
    void disableGameOptions();
    void addPlayer( int ID, QString name, bool readyStatus);
    CatanPlayer* getPlayer(int ID);
    void setHost( int ID );
    Ui::ScreenGameLobby *ui;
    QTimer *timer;
    QTime startTime;
    QMap<CatanPlayer*, bool> readyMap;
    QMap<CatanPlayer*, PlayerReadyWidget*> playerMap;
    int hostID;
};

#endif // SCREENGAMELOBBY_H
