#include "dicedialog.h"
#include "ui_dicedialog.h"

#include <QPaintEvent>
#include <QTimer>
#include <QDebug>
#include "client/managers/networkmanager.h"

DiceDialog::DiceDialog() :
    QDialog(0,
            Qt::CustomizeWindowHint |
            Qt::FramelessWindowHint),
    ui(new Ui::DiceDialog)
{
    ui->setupUi(this);

    qsrand(QTime::currentTime().msec());
    // Setup the timer that determins how long before the dice are
    // rolled again.
    timer = new QTimer(this);
    timer->setInterval( 500 );

    // Make a connection, so that when the timer runs out of time, it
    // will call the roll slot.
    connect( timer, SIGNAL(timeout() ),
             this, SLOT(roll()) );
    connect( net::Connection, SIGNAL(receivedGamePlayersTurn(QDataStream&)),
             this, SLOT(receivedGamePlayersTurn()));
    connect( net::Connection, SIGNAL(receivedGameRollResult(QDataStream&)),
             this, SLOT(receivedGameRollResult(QDataStream&)));

    setAutoFillBackground(false);
    setStyleSheet("background-color: transparent;");
    // This line is necessary because it paints it to the form once.
    roll();
}

void DiceDialog::receivedGamePlayersTurn()
{
    // This will start once the signal has been received indicating
    // it's the players turn.
    timer->start();
}

void DiceDialog::receivedGameRollResult(QDataStream &msg)
{
    int result1;
    int result2;
    msg >> result1;
    msg >> result2;

    timer->stop();
    ui->dice1->setStyleSheet(tr("border-image: url(:/dice/d%0) 0;").arg(result1));
    ui->dice2->setStyleSheet(tr("border-image: url(:/dice/d%0) 0;").arg(result2));
}

void DiceDialog::roll()
{
    int x;
    int y;
    x = qrand() % 6 + 1;
    y = qrand() % 6 + 1;
    ui->dice1->setStyleSheet(tr("border-image: url(:/dice/d%0) 0;").arg(x));
    ui->dice2->setStyleSheet(tr("border-image: url(:/dice/d%0) 0;").arg(y));
}


DiceDialog::~DiceDialog()
{
    delete ui;
}
