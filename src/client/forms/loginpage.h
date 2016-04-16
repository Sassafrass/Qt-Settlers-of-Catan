#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include <QHostAddress>

namespace Ui {
class LoginPage;
}

class LoginPage : public QWidget
{
    Q_OBJECT
    
public:
    explicit LoginPage(QWidget *parent = 0);
    ~LoginPage();
signals:
    void connectToServer(QHostAddress &address, quint16 port);
private slots:
    void connectToServer();
    void ShowSeverButtons();
    void enableConnectButton();
private:
    Ui::LoginPage *ui;
    bool hostPortHidden;
};

#endif // LOGINPAGE_H
