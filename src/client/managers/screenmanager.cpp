#include <QMainWindow>

#include "screenmanager.h"
#include "shared/qout.h"
#include "client/screens/catanscreen.h"

const int ScreenTransitionSpeed = 1000;

ScreenManager::ScreenManager(QMainWindow *window) :
    QObject(window), mainWindow(window), activeScreen(0)
{
    logoWidget = new LogoWidget(window);
    logoWidget->adjustSize();
    logoWidget->move( QPoint( mainWindow->width()*0.5 - logoWidget->width() * 0.5,
                              -logoWidget->height()));
}

CatanScreen* ScreenManager::GetScreen(SCREEN_NAME::ENUM enumPage) const
{
    return screenMap[enumPage];
}

bool ScreenManager::IsCurrentScreen(SCREEN_NAME::ENUM screen)
{
    return currentScreen == screen;
}

void ScreenManager::AddScreen(const SCREEN_NAME::ENUM enumPage, CatanScreen *page)
{
    screenMap[enumPage] = page;
    page->setVisible(false);
    page->setEnabled(false);
    page->SetActive(false);
    page->resize(mainWindow->size());
    connect(this, SIGNAL(keyPressEvent(QKeyEvent*)),
            page, SLOT(keyPressEvent( QKeyEvent *)));
}

void ScreenManager::ForceSetScreen(SCREEN_NAME::ENUM screen)
{
    CatanScreen *newScreen = screenMap[screen];
    if( activeScreen )
    {
        activeScreen->setVisible(false);
        activeScreen->setEnabled(false);
        activeScreen->SetActive(false);
        activeScreen->setFocusPolicy(Qt::NoFocus);
    }
    activeScreen = newScreen;
    newScreen->move(QPoint(0,0));
    newScreen->setEnabled(true);
    newScreen->SetActive(true);
    newScreen->setVisible(true);
    newScreen->setFocusPolicy(Qt::StrongFocus);
    newScreen->setFocus();
    currentScreen = screen;
    moveLogo();
}

void ScreenManager::SetScreen(SCREEN_NAME::ENUM screen)
{
    //if( !screenMap.contains(screen) )
    //{
    //    LOG_ERROR( "Tried to set active screen to non-existant screen");
    //    return;
    //}
    CatanScreen *newScreen = screenMap[screen];
    Q_ASSERT( newScreen );

    if( activeScreen == newScreen )
        return;

    if( activeScreen )
    {
        QPoint deltaPos = newScreen->GetPos() - activeScreen->GetPos();

        activeScreen->SlideTo(QPoint(mainWindow->width()*-deltaPos.x(),
                                     mainWindow->height()*-deltaPos.y()),
                                     ScreenTransitionSpeed //speed
                              );
        activeScreen->setEnabled(false);
        activeScreen->SetActive(false);
        activeScreen->setFocusPolicy(Qt::NoFocus);

        newScreen->move(QPoint(mainWindow->width()*deltaPos.x(),
                               mainWindow->height()*deltaPos.y()));
        newScreen->SlideTo(QPoint(0,0), ScreenTransitionSpeed);

        connect( activeScreen, SIGNAL(SlideFinished()),
                 this, SLOT(hideScreen()) );
    }
    else
    {
        newScreen->move(QPoint(0,0));
        newScreen->setEnabled(true);
    }
    activeScreen = newScreen;
    newScreen->SetActive(true);
    newScreen->setVisible(true);
    newScreen->setFocusPolicy(Qt::StrongFocus);
    //newScreen->setFocus();
    currentScreen = screen;

    moveLogo();
    newScreen->setFocus();
}



void ScreenManager::hideScreen()
{
    CatanScreen *screen = qobject_cast<CatanScreen*>(sender());
    if( !screen ) return;

    screen->setVisible(false);

    disconnect( screen, SIGNAL(SlideFinished()),
                this, SLOT(hideScreen()));

    activeScreen->setEnabled(true);
}

void ScreenManager::moveLogo()
{
    if( activeScreen == screenMap[SCREEN_NAME::GAMEBOARD] /*TODO: Make this GAME*/ )
        logoWidget->setVisible(false);
    else
        logoWidget->setVisible(true);

    if( activeScreen == screenMap[SCREEN_NAME::LOGIN] )
    {
        QPoint centerTop( mainWindow->width() * 0.5 - logoWidget->width() * 0.5, 0 );
        logoWidget->SlideTo(centerTop, ScreenTransitionSpeed);
    }
    else
    {
        QPoint centerBottom( mainWindow->width() * 0.5 - logoWidget->width() * 0.5,
                             mainWindow->height() - logoWidget->height() );
        logoWidget->SlideTo(centerBottom, ScreenTransitionSpeed);
    }
}

