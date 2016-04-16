#include "logowidget.h"
#include "ui_logowidget.h"

LogoWidget::LogoWidget(QWidget *parent) :
     SlidingWidget(parent),
    ui(new Ui::LogoWidget)
{
    ui->setupUi(this);
}

LogoWidget::~LogoWidget()
{
    delete ui;
}
