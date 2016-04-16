#include <QKeyEvent>

#include "screencreate.h"
#include "ui_screencreate.h"
#include "client/managers/networkmanager.h"

ScreenCreate::ScreenCreate(QWidget *parent, ScreenManager *manager, const QPoint &pos) :
    CatanScreen(parent, manager , pos),
    ui(new Ui::ScreenCreate)
{
    ui->setupUi(this);

    connect( ui->buttonBack, SIGNAL(clicked()),
             this, SLOT(gotoMenuScreen()));
    connect( ui->buttonCreate, SIGNAL(clicked()),
             this, SLOT(create()));
}

void ScreenCreate::Activated()
{
    ui->buttonCreate->setEnabled(true);
}

void ScreenCreate::keyPressEvent(QKeyEvent *keyEvent)
{
    if(GetActive())
    {
        if(keyEvent->key() == Qt::Key_Right)
        {
             gotoMenuScreen();
        }
    }
}

void ScreenCreate::gotoMenuScreen()
{
    manager->SetScreen(SCREEN_NAME::MAIN_MENU);
}

ScreenCreate::~ScreenCreate()
{
    delete ui;
}

void ScreenCreate::create()
{
    if(ui->lineGameName->displayText() == "")
    {
        setErrorText("Please enter a game name.");
    }
    else
    {
        net::Begin(NETWORK_COMMAND::CLIENT_CREATE);
            net::AddString(ui->lineGameName->displayText());
            net::AddByte(ui->spinPlayerSelect->value());
            net::AddBool((ui->comboBoxMaritimeTrade->currentText() == "Enabled"));
            net::AddBool((ui->comboBoxChits->currentText() == "Random"));
        net::Send();

        ui->buttonCreate->setEnabled(false);
        manager->SetScreen(SCREEN_NAME::READY_ROOM);
    }
}

void ScreenCreate::setErrorText(QString errorTxt)
{
    ui->labelError->setText("<font color=#FF0000>"+errorTxt+"</font>");
}
