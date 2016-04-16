/****************************************************************************
** **Settlers of Catan**
** LoginWidget
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** This class is created in the ScreenLogin.
** it is used to connect the screen and the network it sets up the network
**
****************************************************************************/

#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include <QHostAddress>

#include "client/widgets/slidingwidget.h"

namespace Ui {
class LoginPage;
}

class LoginWidget : public SlidingWidget
{
    Q_OBJECT
    
public:
    explicit LoginWidget(QWidget *parent = 0);
    QString GetName() const;
    void SetErrorText(QString errorTxt);
    ~LoginWidget();
signals:
    void connectToServer(QHostAddress &address, quint16 port);
public slots:
    void connectToServer();
private slots:
    void ShowSeverButtons();
    void enableConnectButton();
private:
    Ui::LoginPage *ui;
    bool hostPortHidden;
};

#endif // LOGINPAGE_H
