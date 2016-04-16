#include <QMessageBox>

#include "forms/loginpage.h"
#include "ui_loginpage.h"
#include <QDebug>

LoginPage::LoginPage(QWidget *parent) :
    QWidget(parent),
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
    connect( ui->lineEditUsername, SIGNAL(returnPressed()), this, SLOT(connectToServer()));
    connect( ui->lineEditHost, SIGNAL(returnPressed()), this, SLOT(connectToServer()));
    connect( ui->labelPort, SIGNAL(returnPressed()), this, SLOT(connectToServer()));
}

void LoginPage::connectToServer()
{
    if(!ui->ButtonConnect->isEnabled())
        return;

    if(ui->lineEditUsername->text() == "")
    {
        QMessageBox::information(this, tr("Catan Client"),
                                 tr("Please enter a username."));
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

void LoginPage::ShowSeverButtons()
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

void LoginPage::enableConnectButton()
{
    ui->ButtonConnect->setEnabled(true);
    ui->lineEditHost->setEnabled(true);
    ui->lineEditPort->setEnabled(true);
    ui->lineEditUsername->setEnabled(true);
}

LoginPage::~LoginPage()
{
    delete ui;
}
