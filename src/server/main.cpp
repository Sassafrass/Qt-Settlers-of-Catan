// #include <windows.h>
#include <QtCore/QCoreApplication>
#include "shared/qout.h"
#include "server/server.h"

#define SERVER

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    a.setOrganizationName( "Bronies" );
    a.setApplicationName( "Settlers of Catan Server" );

    LOG_INFO("Starting Settlers of Catan Server! Welcome!" << endl);

    CatanServer server;
    QMetaObject::invokeMethod( &server, "start", Qt::QueuedConnection );

    return a.exec();
}
