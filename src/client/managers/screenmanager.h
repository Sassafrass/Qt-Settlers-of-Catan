    /****************************************************************************
** **Settlers of Catan**
** ScreenManager
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** the screen manager is used so that we can easily slide screens on and off
** the main window this is good so that we can do the sliding animaition with
** one function.
****************************************************************************/


#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <QMap>
#include <QObject>
#include <QWidget>
#include "client/enums/screen.h"
#include "client/widgets/logowidget.h"

class QMainWindow;
class CatanScreen;

class ScreenManager : public QObject
{
    Q_OBJECT
public:
    ScreenManager(QMainWindow *window);
    void AddScreen(SCREEN_NAME::ENUM, CatanScreen*);
    void ForceSetScreen(SCREEN_NAME::ENUM);
    void SetScreen(SCREEN_NAME::ENUM);
    bool IsCurrentScreen(SCREEN_NAME::ENUM);
    CatanScreen* GetScreen(SCREEN_NAME::ENUM) const;
signals:
    void keyPressEvent(QKeyEvent *);
private slots:
    void hideScreen();
private:
    QMainWindow *mainWindow;
    CatanScreen *activeScreen;
    SCREEN_NAME::ENUM   currentScreen;
    LogoWidget *logoWidget;
    QMap<SCREEN_NAME::ENUM, CatanScreen*> screenMap;

    void moveLogo();
};

#endif // SCREENMANAGER_H
