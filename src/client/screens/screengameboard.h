/****************************************************************************
** **Settlers of Catan**
** ScreenGameBoard
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** From: ScreenLobby To: JoinCreateScreen
** This Screen uses the Renderable object to create the board.
** if you want to add to the screen you must use the boardScene.
** It is required that you use Qdialogs so that you can add any widget to the screen.
**
** TODO:
** Implement the clicking so that we can place roads and cities.
** lots to do hook up the world.
**
****************************************************************************/

#ifndef SCREENGAMEBOARD_H
#define SCREENGAMEBOARD_H

#include <QWidget>

#include "client/screens/catanscreen.h"

class CatanPlayer;
class CatanBoard;
class PlayerHandWidget;
class ScreenManager;
class GraphicsView;
class CatanBoardScene;
class PlayerStatusDialog;

class ScreenGameBoard : public CatanScreen
{
    Q_OBJECT
    
public:
    explicit ScreenGameBoard(QWidget *parent, ScreenManager *manager, const QPoint &pos);
    void SetPlayers(const QVector<CatanPlayer*> &players);
    ~ScreenGameBoard();
    void GenerateBoard(uint seed, int playerCount);
protected slots:
    virtual void resizeEvent(QResizeEvent *);
    virtual void Activated();
    virtual void Deactivated();
private slots:
private:
    void setupCards();
    void setupDice();
    //CatanGame *catanGame;
    PlayerHandWidget *playerHand;
    CatanBoard *board;
    CatanBoardScene *boardScene;
    GraphicsView *view;
    QMap<CatanPlayer*, PlayerStatusDialog*> playerMap;
};

#endif // SCREENGAMEBOARD_H
