#include <QKeyEvent>

#include "screenmainmenu.h"
#include "ui_screenmainmenu.h"
#include "client/managers/screenmanager.h"



ScreenMainMenu::ScreenMainMenu(QWidget *parent, ScreenManager *manager, const QPoint &pos) :
    CatanScreen(parent, manager, pos),
    ui(new Ui::ScreenMainMenu)
{
    ui->setupUi(this);
    connect(ui->buttonJoin, SIGNAL(clicked()), this , SLOT(gotoJoinScreen()));
    connect(ui->buttonCreate, SIGNAL(clicked()), this, SLOT(gotoCreateScreen()));

}

void ScreenMainMenu::keyPressEvent(QKeyEvent *keyEvent)
{
    if( !GetActive() ) return;

    if(keyEvent->key() == Qt::Key_Right || keyEvent->key() == Qt::Key_D)
    {
        gotoJoinScreen();
    }
    else if(keyEvent->key() == Qt::Key_Left || keyEvent->key() == Qt::Key_A)
    {
        gotoCreateScreen();
    }
}

void ScreenMainMenu::gotoJoinScreen()
{
    manager->SetScreen(SCREEN_NAME::LOBBY);
}

void ScreenMainMenu::gotoCreateScreen()
{
    manager->SetScreen(SCREEN_NAME::CREATE_ROOM);
}

ScreenMainMenu::~ScreenMainMenu()
{
    delete ui;
}
