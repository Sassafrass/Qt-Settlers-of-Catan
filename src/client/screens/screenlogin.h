/****************************************************************************
** **Settlers of Catan**
** ScreenLogin
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** From: NULL  To: ScreenJoinCreate
** This screen joins the screen and setup the network connection.
** Uses the network class and setups the name space
**
****************************************************************************/


#ifndef SCREENLOGIN_H
#define SCREENLOGIN_H

#include <QWidget>
#include <QHostAddress>
#include "client/screens/catanscreen.h"

class ScreenManager;
class LoginWidget;
class LogoWidget;

namespace Ui {
class ScreenLogin;
}

class ScreenLogin : public CatanScreen
{
    Q_OBJECT
public:
    explicit ScreenLogin(QWidget *parent, ScreenManager *manager, const QPoint &pos);
    ~ScreenLogin();
public slots:
    void keyPressEvent(QKeyEvent *);
private slots:
    void resizeEvent(QResizeEvent *);
    void connectToServer(QHostAddress &address, quint16 port);
    void onDisconnect();
    void onConnectionReady();
    void displayError(QAbstractSocket::SocketError socketError);
private:
    Ui::ScreenLogin *ui;
    LoginWidget *w_login;
};

#endif // SCREENLOGIN_H
