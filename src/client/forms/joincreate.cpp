#include "joincreate.h"
#include "ui_joincreate.h"

JoinCreate::JoinCreate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JoinCreate)
{
    ui->setupUi(this);
}

JoinCreate::~JoinCreate()
{
    delete ui;
}
