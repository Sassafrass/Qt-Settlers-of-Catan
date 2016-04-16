#include <QMessageBox>
#include <QDebug>

#include "client/widgets/login.h"
#include "ui_login.h"


LoginWidget::LoginWidget(QWidget *parent) :
    SlidingWidget(parent),
    ui(new Ui::LoginPage)
{
    ui->setupUi(this);
    hostPortHidden = true;
    ui->labelHost->setHidden(true);
    ui->lineEditHost->setHidden(true);
    ui->labelPort->setHidden(true);
    ui->lineEditPort->setHidden(true);
    connect( ui->ButtonConnect, SIGNAL(clicked()), this, SLOT(connectToServer()));
    connect( ui->toolButton, SIGNAL(clicked()), this, SLOT(ShowSeverButtons()));
}

QString LoginWidget::GetName() const
{
    return ui->lineEditUsername->displayText();
}

void LoginWidget::connectToServer()
{
    if(!ui->ButtonConnect->isEnabled())
        return;

    if(ui->lineEditUsername->text() == "")
    {
        SetErrorText("Please enter a username.");
    }
    else
    {

        ui->ButtonConnect->setEnabled(false);
        ui->lineEditHost->setEnabled(false);
        ui->lineEditPort->setEnabled(false);
        ui->lineEditUsername->setEnabled(false);
        qDebug() << ui->lineEditHost->displayText();
        QHostAddress address;
        address.setAddress(ui->lineEditHost->displayText());
        emit connectToServer(address, ui->lineEditPort->displayText().toInt());
    }
}

void LoginWidget::SetErrorText(QString errorTxt)
{
    ui->labelError->setText("<font color=#FF0000>"+errorTxt+"</font>" );
}

void LoginWidget::ShowSeverButtons()
{
    if(hostPortHidden)
    {
        hostPortHidden = false;
        ui->labelHost->setHidden(false);
        ui->lineEditHost->setHidden(false);
        ui->labelPort->setHidden(false);
        ui->lineEditPort->setHidden(false);
    }
    else
    {
        hostPortHidden = true;
        ui->labelHost->setHidden(true);
        ui->lineEditHost->setHidden(true);
        ui->labelPort->setHidden(true);
        ui->lineEditPort->setHidden(true);
    }
}

void LoginWidget::enableConnectButton()
{
    ui->ButtonConnect->setEnabled(true);
    ui->lineEditHost->setEnabled(true);
    ui->lineEditPort->setEnabled(true);
    ui->lineEditUsername->setEnabled(true);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}
