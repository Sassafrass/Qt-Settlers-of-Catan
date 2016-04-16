    #include <QIcon>
#include <QPixmap>
#include <QStandardItem>
#include "playerreadywidget.h"
#include "ui_playerreadywidget.h"
#include "client/enums/c_playercolor.h"
#include "client/managers/networkmanager.h"

PlayerReadyWidget::PlayerReadyWidget(CatanPlayer *player, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomListWidget)
{
    ui->setupUi(this);
    ui->labelPlayer1->setText(player->GetName());
    QPixmap pix(20,20);
    for(int i = PLAYER_COLOR::RED; i != PLAYER_COLOR::NONE ;i++)
    {
        const QColor color = PLAYER_COLOR::toColor(static_cast<PLAYER_COLOR::ENUM>(i));
        pix.fill(color);
        ui->comboBoxColor->addItem(QIcon(pix),"");
    }
    ui->checkBoxReadyHost->setCheckable(true);
    connect(player, SIGNAL(destroyed()),
            this, SLOT(deleteLater()));

    //WHEN COLOR WORKS DISPLAY
    ui->comboBoxColor->setHidden(true);
}

void PlayerReadyWidget::readyToggled(bool state)
{
    net::Begin(NETWORK_COMMAND::PLAYER_READY);
        net::AddBool(state);
    net::Send();
}

void PlayerReadyWidget::SetHost(bool host)
{
    if( host )
        ui->kingIcon->setStyleSheet("background-image: url(:/icons/images/icons/room_king.png)");
    else
        ui->kingIcon->setStyleSheet("");
}

void PlayerReadyWidget::SetReadyCheckBox(bool state)
{
    ui->checkBoxReadyHost->setChecked(state);

}

void PlayerReadyWidget::SetController(bool hasControl)
{
    controller = hasControl;
    if( hasControl )
    {
        connect(ui->checkBoxReadyHost, SIGNAL(toggled(bool)),
                this, SLOT(readyToggled(bool)));
    }
    else
    {
        disconnect(ui->checkBoxReadyHost, SIGNAL(toggled(bool)),
                this, SLOT(readyToggled(bool)));
        disablePlayerButtons();
    }
}

void PlayerReadyWidget::disablePlayerButtons()
{
    ui->checkBoxReadyHost->setEnabled(false);
    ui->comboBoxColor->setEnabled(false);
}

PlayerReadyWidget::~PlayerReadyWidget()
{
    delete ui;
}
