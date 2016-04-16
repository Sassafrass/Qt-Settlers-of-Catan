#include "yourhandwidget.h"
#include "ui_yourhandwidget.h"

YourHandWidget::YourHandWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::YourHandWidget)
{
    ui->setupUi(this);
}

YourHandWidget::~YourHandWidget()
{
    delete ui;
}
