/****************************************************************************
** **Settlers of Catan**
** Development Card Enumeration
** author: Team Bronies
** date: 4/25/2012
**
** The CatanPlayerBase class serves as a base for the Server or Client player
** class.  The base contains shared code between client and server versions
** of the catan player.
****************************************************************************/

#ifndef SH_PLAYER_H
#define SH_PLAYER_H

#include <QObject>
#include <QList>
#include "shared/enums/playercolor.h"
#include "shared/enums/playerstate.h"
#include "shared/hand.h"

typedef quint8 PlayerID;

class CatanPiece;
class CatanSettlement;

class CatanPlayerBase : public QObject
{
    Q_OBJECT
public:
    explicit CatanPlayerBase(PlayerID ID, QObject *parent);
    virtual ~CatanPlayerBase();
    PlayerColor GetColor() const;

    /**
      * Returns the player's hand.
      */
    PlayerHand* GetPlayerHand() const;

    QList<CatanPiece*> GetActivePieces() const;
    QList<CatanSettlement*> GetSettlements() const;
    void AddResource(RESOURCE::ENUM res, int count=1);
    void SetColor(const PlayerColor& color);
    void SetState(PLAYER_STATE::ENUM state);
    PLAYER_STATE::ENUM GetState() const;
    QString GetName() const;
    PlayerID GetID() const;
signals:
public slots:
private:
    void createPieces();
protected:
    PlayerID ID;
    QString name;
    PlayerColor color;
    PLAYER_STATE::ENUM state;

    //the cards in this player's hand
    PlayerHand *hand;
    QList<CatanPiece*> passivePieces;
    QList<CatanPiece*> activePieces;
};

#endif // SH_PLAYER_H
