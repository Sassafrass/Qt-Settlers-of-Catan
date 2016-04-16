/****************************************************************************
** **Settlers of Catan**
** ScreenCreate
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** Slide from ScreenJoin and Slides to GameLobby
** This screen has a bunch of option buttons that are sent to the sever when you create.
** You can as well choose if you would like 4 or 6 players
**
****************************************************************************/

#ifndef SCREENCREATE_H
#define SCREENCREATE_H

#include <QWidget>

#include "client/screens/catanscreen.h"

namespace Ui {
class ScreenCreate;
}

class ScreenCreate : public CatanScreen
{
    Q_OBJECT
    
public:
    explicit ScreenCreate(QWidget *parent, ScreenManager *manager, const QPoint &pos);
    ~ScreenCreate();
protected:
    virtual void Activated();
    void keyPressEvent(QKeyEvent *);
private slots:
    void gotoMenuScreen();
    void create();
private:
    void setErrorText(QString error);
    Ui::ScreenCreate *ui;
};

#endif // SCREENCREATE_H
