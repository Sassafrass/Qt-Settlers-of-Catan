#include <QtGui/QApplication>
#include "forms/mainwindow.h"

#define CLIENT

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow *win = new MainWindow();
    win->show();

    return a.exec();
}
