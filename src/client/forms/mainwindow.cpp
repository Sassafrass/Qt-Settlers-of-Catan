
#include <QDebug>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

#include "mainwindow.h"

#include "client/client.h"
#include "client/enums/screen.h"
#include "client/managers/screenmanager.h"
#include "client/managers/networkmanager.h"
#include "client/screens/screenlogin.h"
#include "client/screens/screenmainmenu.h"
#include "client/screens/screenjoin.h"
#include "client/screens/screencreate.h"
#include "client/screens/screengamelobby.h"
#include "client/screens/screengameboard.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    conn = new ClientConnection(this);
    net::Connection = conn;

    this->resize( 1024, 768 );
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setMinimumSize( width(), height() );
    this->setMaximumSize( width(), height() );

    screenManager = new ScreenManager(this);
    screenManager->AddScreen(SCREEN_NAME::LOGIN,
                             new ScreenLogin(
                                 this,
                                 screenManager,
                                 QPoint(0,0)
                                 )
                             );
    screenManager->AddScreen(SCREEN_NAME::MAIN_MENU,
                             new ScreenMainMenu(
                                 this,
                                 screenManager,
                                 QPoint(0,-1)
                                 )
                             );
    screenManager->AddScreen(SCREEN_NAME::LOBBY,
                             new ScreenJoin(
                                 this,
                                 screenManager,
                                 QPoint(1,-1)
                                 )
                             );
    screenManager->AddScreen(SCREEN_NAME::CREATE_ROOM,
                             new ScreenCreate(
                                this,
                                 screenManager,
                                 QPoint(-1,-1)
                                 )
                             );
    screenManager->AddScreen(SCREEN_NAME::READY_ROOM,
                             new ScreenGameLobby(
                                this,
                                screenManager,
                                 QPoint(-1,-2)
                                 )
                             );
    screenManager->AddScreen(SCREEN_NAME::GAMEBOARD,
                             new ScreenGameBoard(
                                 this,
                                 screenManager,
                                 QPoint(0,-2)
                                 )
                             );

    screenManager->SetScreen(SCREEN_NAME::LOGIN);

    connect(this, SIGNAL(keyPressEvent(QKeyEvent*)),
            screenManager, SIGNAL(keyPressEvent(QKeyEvent*)));
   // FADESETUP(ui, login);
//    QGraphicsOpacityEffect* fade_effect = new QGraphicsOpacityEffect(p_login);
//    this->setGraphicsEffect(fade_effect);
//    QPropertyAnimation *fadeanimation = new QPropertyAnimation(fade_effect, "opacity");
//      fadeanimation->setEasingCurve(QEasingCurve::InOutQuad);
//      fadeanimation->setDuration(500);
//      fadeanimation->setStartValue(0.01);
//      fadeanimation->setEndValue(1.0);
//      fadeanimation->start(QPropertyAnimation::DeleteWhenStopped);

//    p_login->setGraphicsEffect(fade_effect);

}


void MainWindow::resizeEvent(QResizeEvent *)
{
}

MainWindow::~MainWindow()
{
}
