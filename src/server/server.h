/****************************************************************************
** **Settlers of Catan**
** Development Card Enumeration
** author: Team Bronies
** date: 4/25/2012
**
** The CatanServer is the main object of the program.  It stores all of
** the client connections, the lobby manager, and the game manager.
****************************************************************************/

#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>

class QLocalServer;
class QNetworkSession;
class QTcpServer;
class ClientConnection;
class CatanUser;
class LobbyManager;
class GameManager;

class CatanServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit CatanServer(QObject *parent = 0);
    const QList<CatanUser*> GetUsers() const;
    GameManager* GetGameManager() const;
signals:
    void newConnection(ClientConnection *connection);
public slots:
    void start();
private slots:
    void onUserDisconnected();
    void onUserAuth();
private:
    QList<CatanUser*> users;

    LobbyManager *lobbyManager;
    GameManager *gameManager;
protected:
    void incomingConnection(int socketDescriptor);
};

#endif // SERVER_H
