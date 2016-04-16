#include "gameboard.h"
#include "ui_gameboard.h"

gameboard::gameboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameboard)
{
    ui->setupUi(this);
}

gameboard::~gameboard()
{
    delete ui;
}
