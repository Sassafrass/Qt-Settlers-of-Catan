/****************************************************************************
** **Settlers of Catan**
** ScreenMainMenu
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** From: ScreenJoin, ScreenCreate, ScreenLogin To: ScreenCreate, ScreenCreate
** This screen is two button that go from login to the ScreenJoin, or ScreenCreate
**
****************************************************************************/

#ifndef SCREENMAINMENU_H
#define SCREENMAINMENU_H

#include <QWidget>
#include "client/screens/catanscreen.h"

namespace Ui {
class ScreenMainMenu;
}

class ScreenMainMenu : public CatanScreen
{
    Q_OBJECT
    
public:
    explicit ScreenMainMenu(QWidget *parent, ScreenManager *manager, const QPoint &pos);
    ~ScreenMainMenu();
signals:
protected:
public slots:
    void keyPressEvent(QKeyEvent *);
private slots:
    void gotoJoinScreen();
    void gotoCreateScreen();
private:
    Ui::ScreenMainMenu *ui;
};

#endif // SCREENMAINMENU_H
