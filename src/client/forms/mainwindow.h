/****************************************************************************
** **Settlers of Catan**
** CatanClient
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** The Main window was used so that screens could slide on and off the window\
** The main window has a screen manager that is used so that we can easly slide off
** It also in the main ui component.
** It will one day be resizable.
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ClientConnection;
class LoginWidget;
class ScreenManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void resizeEvent(QResizeEvent *);
    //void paintEvent(QPaintEvent *);
signals:
    void keyPressEvent(QKeyEvent *);
private:
    ClientConnection *conn;
    ScreenManager *screenManager;
    //MainLobby *p_lobby;
};

#endif // MAINWINDOW_H
