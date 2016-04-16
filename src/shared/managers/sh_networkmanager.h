/****************************************************************************
** **Settlers of Catan**
** Development Card Enumeration
** author: Team Bronies
** date: 4/25/2012
**
** The NetworkManager is actually a network interface for making sending
** messages between the client and the server easier to maintain.
** The goal is to create an abstract and easy way to start and commit
** a message to a TcpSocket connection.
****************************************************************************/

#ifndef SH_NETWORKMANAGER_H
#define SH_NETWORKMANAGER_H

#include <QObject>
#include "shared/enums/command.h"

class Connection;

namespace net {

void Begin(NetworkCommand);
void AddByte(quint8 c);
void AddBool(bool b);
void AddChar(QChar c);
void AddString(QString s);
void AddShort(quint16 s);

} //namespace net

class NetworkManager : public QObject
{

    Q_OBJECT
public:
    static NetworkManager* getInstance();
    void Begin(NetworkCommand);
    void AddByte(quint8 c);
    void AddBool(bool c);
    void AddChar(QChar c);
    void AddString(QString s);
    void AddShort(quint16 s);
    void Send(const QList<Connection*> &rf);
    void Send(Connection* conn);
private:
    NetworkManager() : stream(0) {}
    NetworkManager(const NetworkManager &); // hide copy constructor
    NetworkManager& operator=(const NetworkManager &); // hide assign op

    static NetworkManager* instance_;
    QByteArray buffer;
    QDataStream *stream;

};

#endif // SH_NETWORKMANAGER_H
