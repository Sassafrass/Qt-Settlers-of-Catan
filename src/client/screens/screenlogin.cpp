#include <QPainter>
#include <QMessageBox>
#include <QKeyEvent>

#include "screenlogin.h"
#include "ui_screenlogin.h"
#include "client/widgets/login.h"
#include "client/widgets/logowidget.h"
#include "client/managers/networkmanager.h"
#include "client/enums/screen.h"

ScreenLogin::ScreenLogin(QWidget *parent, ScreenManager *manager, const QPoint &pos) :
    CatanScreen(parent, manager, pos),
    ui(new Ui::ScreenLogin)
{
    ui->setupUi(this);

    w_login = new LoginWidget(this);

    connect( w_login, SIGNAL(connectToServer(QHostAddress&,quint16)),
             this, SLOT(connectToServer(QHostAddress&,quint16)));
    connect( net::Connection, SIGNAL(disconnected()),
            w_login ,SLOT(enableConnectButton()));
    connect( net::Connection, SIGNAL(error(QAbstractSocket::SocketError)),
            w_login ,SLOT(enableConnectButton()));
    connect( net::Connection, SIGNAL(error(QAbstractSocket::SocketError)),
             this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect( net::Connection, SIGNAL(disconnected()),
             this, SLOT(onDisconnect()));
    connect( net::Connection, SIGNAL(readyForUse()),
             this, SLOT(onConnectionReady()));
}

void ScreenLogin::resizeEvent(QResizeEvent*)
{
    w_login->Center();
}

void ScreenLogin::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        w_login->SetErrorText("The host was not found. Please check the "
                              "host name and port settings.");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        w_login->SetErrorText("The connection was refused by the peer. "
                              "Make sure the fortune server is running, "
                              "and check that the host name and port "
                              "settings are correct.");
        break;
    default:
        w_login->SetErrorText(tr("The following error occurred: %1.")
                              .arg(net::Connection->errorString()));
    }
}

void ScreenLogin::keyPressEvent(QKeyEvent *e)
{
    if( !GetActive() ) return;

    if( e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return )
        w_login->connectToServer();
}

void ScreenLogin::onDisconnect()
{
    QMessageBox::information(this, tr("Message"),
                             tr("You have disconnected from the server"));
    manager->ForceSetScreen(SCREEN_NAME::LOGIN);
}

void ScreenLogin::onConnectionReady()
{
    //Send Greeting
    net::Begin(NETWORK_COMMAND::GREETING);
    net::Send();

    net::Connection->SetName(w_login->GetName());
    net::Begin(NETWORK_COMMAND::CLIENT_NAME);
        net::AddString(w_login->GetName());
    net::Send();

    manager->SetScreen(SCREEN_NAME::MAIN_MENU);
    //TODO: Refactor this animation stuff
//    QGraphicsOpacityEffect* fade_effect = new QGraphicsOpacityEffect(p_login);
//    this->setGraphicsEffect(fade_effect);
//    QPropertyAnimation *fadeanimation = new QPropertyAnimation(fade_effect, "opacity");
//      fadeanimation->setEasingCurve(QEasingCurve::InOutQuad);
//      fadeanimation->setDuration(500);
//      fadeanimation->setStartValue(1.0);
//      fadeanimation->setEndValue(0.0);
//      fadeanimation->start(QPropertyAnimation::DeleteWhenStopped);

    //p_login->setGraphicsEffect(fade_effect);

    //Testing network interface
    //TestForm *test = new TestForm(this);
    //test->show();
}

void ScreenLogin::connectToServer(QHostAddress& address, quint16 port)
{

    qDebug() << "Connecting to host";
    net::Connection->abort();
    net::Connection->connectToHost( address, port );

}

ScreenLogin::~ScreenLogin()
{
    delete ui;
}
