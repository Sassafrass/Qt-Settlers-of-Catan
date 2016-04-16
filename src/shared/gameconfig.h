/****************************************************************************
** **Settlers of Catan**
** Development Card Enumeration
** author: Team Bronies
** date: 4/25/2012
**
** This object stores all of the configuration options of a CatanGame.
****************************************************************************/

#ifndef CATANGAMECONFIGURATION_H
#define CATANGAMECONFIGURATION_H

#include <QObject>

class CatanGameConfiguration : public QObject
{
    Q_OBJECT
public:
    explicit CatanGameConfiguration(QObject *parent = 0);
    int GetMaxPlayers() const;
    bool GetRandomChits() const;
    bool GetMaritimeTrading() const;
    void SetMaxPlayers(int max);
    void SetRandomChits(bool);
    void SetMaritimeTrading(bool);

signals:
    
public slots:
private:
    int maxPlayers;
    bool randomChits;
    bool maritimeTrade;
};

#endif // CATANGAMECONFIGURATION_H
