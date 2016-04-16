/****************************************************************************
** **Settlers of Catan**
** ScreenJoin
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** From: ScreenJoinCreate To: ScreenGameBoard, ScreenJoinCreate
** This has the ability to join a game that is open you can click the join button
** or double click to join a game. If the game is full then you cannot join.
**
****************************************************************************/

#ifndef SCREENJOIN_H
#define SCREENJOIN_H

#include <QWidget>
#include <QtGui>
#include "client/widgets/roomlabel.h"
#include "client/screens/catanscreen.h"

class RoomListWidget;

namespace Ui {
class ScreenJoin;
}

class ScreenJoin : public CatanScreen
{
    Q_OBJECT
    
public:
    explicit ScreenJoin(QWidget *parent, ScreenManager *manager, const QPoint &pos);
    ~ScreenJoin();
protected:
    virtual void Activated();
    virtual void Deactivated();
    void keyPressEvent(QKeyEvent *);

private slots:
    void joinButtonPressed();
    void setCurrentSelected(bool);
    void refreshRoomList();
    void gotoMenuScreen();
    void receivedRoomList(QDataStream&);
    void receivedRoomNew(QDataStream&);
    void receivedRoomClose(QDataStream&);
private:
    Ui::ScreenJoin *ui;
    RoomListWidget *roomList;
    quint16 selected;
};

#endif // SCREENJOIN_H
