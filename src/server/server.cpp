#include <QtNetwork>

#include "shared/qout.h"
#include "server/user.h"
#include "server/client.h"
#include "server/server.h"
#include "server/managers/lobbymanager.h"
#include "server/managers/networkmanager.h"
#include "server/managers/gamemanager.h"
#include "server/entities/player.h"
#include "shared/gameconfig.h"

CatanServer::CatanServer(QObject *parent)
    : QTcpServer(parent)
{
    lobbyManager = new LobbyManager(this);
    gameManager = new GameManager(this);
}

GameManager* CatanServer::GetGameManager() const
{
    return gameManager;
}

/**
 * Server receives a new socket connection
 */
void CatanServer::incomingConnection(int socketDescriptor)
{
    //Create a new client for this socket
    ClientConnection *conn = new ClientConnection(this);
    conn->setSocketDescriptor(socketDescriptor);
    emit newConnection(conn);

    //Create a new user for this client
    CatanUser* user = new CatanUser();
    user->SetConnection(conn);
    conn->setParent(user);
    conn->SetUser(user);

    users.push_back(user);

    //connect to user signals
    connect(user, SIGNAL(disconnected()),
            this, SLOT(onUserDisconnected()));
    connect(user, SIGNAL(RequestCreateRoom(QString, int,bool,bool)),
            lobbyManager, SLOT(RequestCreateRoom(QString, int,bool,bool)));
    connect(user, SIGNAL(RequestListRooms()),
            lobbyManager, SLOT(RequestListRooms()));
    connect(user, SIGNAL(RequestJoinRoom(RoomID)),
            lobbyManager, SLOT(RequestJoinRoom(RoomID)));

    LOG_INFO("A client has connected! " << conn->peerAddress().toString() << endl);

    //send the client a greeting
    net::Begin(NETWORK_COMMAND::GREETING);
    net::Send(conn);

    connect( user, SIGNAL(authenticated()),
             this, SLOT(onUserAuth()));

}

void CatanServer::onUserAuth()
{
    CatanUser *user = qobject_cast<CatanUser*>(sender());
    Q_ASSERT( user );

    CatanPlayer *player = new CatanPlayer(0, user);
    QVector<CatanPlayer*> players;
    players.push_back( player );
    gameManager->CreateGame( new CatanGameConfiguration(lobbyManager), players );
}

/**
 * Handles the event when a user's client-connection disconnects.
 * In some cases, the user should still exist so that the client
 * can re-connect and be re-associated with that user
 **/
void CatanServer::onUserDisconnected()
{
    //get the user who disconnected
    CatanUser *user = qobject_cast<CatanUser*>(sender());
    Q_ASSERT( user );

    if( !user->InGame() )
    {
        //remove the user from the server
        users.removeOne(user);
        user->deleteLater();

        LOG_INFO("User [" << user->name() << "] has disconnected." << endl);

        //disconnect from user's signals (Is this necessary?)
        disconnect(user,       SIGNAL(RequestCreateRoom(QString,int,bool,bool)),
                   lobbyManager, SLOT(RequestCreateRoom(QString,int,bool,bool)));
        disconnect(user,       SIGNAL(RequestListRooms()),
                   lobbyManager, SLOT(RequestListRooms()));
    }
    else //if the user is in the game we don't want to remove them, incase they reconnect
    {
        LOG_INFO("Client of user [" << user->name() << "] disconnected."<< endl);
    }
}

/**
 * Starts the server and opens an IP and port for listening
 **/
void CatanServer::start()
{
    if (!listen(QHostAddress::Any, 11850)) {
        LOG_ERROR( "Unable to start the server " << errorString());
        return;
    }
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    LOG_INFO("The server is running on\n\tIP: " << ipAddress << "\n\tport: " << serverPort() << endl);
}

const QList<CatanUser*> CatanServer::GetUsers() const
{
    return users;
}
