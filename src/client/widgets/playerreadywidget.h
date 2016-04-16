/****************************************************************************
** **Settlers of Catan**
** PlayerReadyWidget
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** This class is used in the ScreenGameLobby and has all the details.
** This is made when a player enters the game and keeps track of player color
** and ready status
**
****************************************************************************/


#ifndef ROOMLISTWIDGET_H
#define ROOMLISTWIDGET_H

#include <QWidget>

#include "client/entities/player.h"

namespace Ui {
class RoomListWidget;
}

class PlayerReadyWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PlayerReadyWidget(CatanPlayer *player,QWidget *parent = 0);
    ~PlayerReadyWidget();
    void disablePlayerButtons();
    void SetHost(bool host);
    void SetReadyCheckBox(bool state);
    void SetController(bool hasControl);
private slots:
    void readyToggled(bool state);
private:
    Ui::RoomListWidget *ui;
    bool controller;
};

#endif // ROOMLISTWIDGET_H
