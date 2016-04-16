
#include <QDebug>

#include "playerstatusdialog.h"
#include "ui_playerstatusdialog.h"
#include "client/entities/player.h"
#include "client/enums/c_playercolor.h"

PlayerStatusDialog::PlayerStatusDialog(CatanPlayer *player) :
    QDialog(0,
            Qt::CustomizeWindowHint |
            Qt::FramelessWindowHint),
    ui(new Ui::PlayerStatusDialog),
    player(player)
{
    ui->setupUi(this);
    layout()->setContentsMargins(0,0,0,0);
    ui->labelPlayerName->setText(player->GetName());
    setWindowOpacity(0.8);

    const QColor &color = PLAYER_COLOR::toColor(player->GetColor());
    setStyleSheet("background-color: transparent;border-color: rgb("+
                            QString::number(color.red()) + ","+
                            QString::number(color.green()) +","+
                            QString::number(color.blue()) +");");

    style()->unpolish(this);
    ensurePolished();
}

PlayerStatusDialog::~PlayerStatusDialog()
{
    delete ui;
}
