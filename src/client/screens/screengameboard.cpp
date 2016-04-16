#include <QResizeEvent>

#include "screengameboard.h"
#include "client/managers/screenmanager.h"
#include "client/managers/networkmanager.h"
#include "client/widgets/boardscene.h"
#include "client/entities/player.h"
#include "client/widgets/playerhandswidget.h"
#include "shared/entities/board.h"
#include "client/widgets/graphicswidget.h"
#include "client/widgets/playerstatusdialog.h"
#include "client/widgets/dicedialog.h"
#include "shared/defines.h"

ScreenGameBoard::ScreenGameBoard(QWidget *parent, ScreenManager *manager, const QPoint &pos) :
    CatanScreen(parent, manager, pos)
{
    //this->layout()->setContentsMargins(0,0,0,0);
    //ui->layoutDice->addWidget(new DiceWidget());
    board = 0;
    view = 0;
    boardScene = 0;

    //GenerateBoard(100, 4);
}

void ScreenGameBoard::Activated()
{
}

void ScreenGameBoard::Deactivated()
{
    if( !view ) return;

    delete board;
    board = 0;
    delete boardScene;
    boardScene = 0;
    delete view;
    view = 0;
}

void ScreenGameBoard::GenerateBoard(uint seed, int playerCount)
{
    if( view ) return;

    QGLWidget *widget = new QGLWidget(this);
    widget->makeCurrent();
    boardScene = new CatanBoardScene(this);
    view = new GraphicsView(this);
    view->resize(size());
    view->setViewport(widget);
    view->setViewportUpdateMode(
        QGraphicsView::FullViewportUpdate);
    view->setScene(boardScene);

    board = new CatanBoard(this, seed);
    board->SetNumPlayers(playerCount);
    board->SetupTiles();
    boardScene->SetBoard(board);
}

void ScreenGameBoard::resizeEvent(QResizeEvent *event)
{
    view->resize(event->size());
}

void ScreenGameBoard::SetPlayers(const QVector<CatanPlayer *> &playerVector)
{
    int xPadding = width() * 0.01;
    int widgetSize = (width() - xPadding*CATAN_MAX_PLAYERS) / CATAN_MAX_PLAYERS ;
    int xOffset = xPadding;
    int yOffset = xOffset;
    foreach(CatanPlayer *player, playerVector)
    {
        PlayerStatusDialog *widget = new PlayerStatusDialog(player);
        widget->show();

        playerMap[player] = widget;
        widget->resize( widgetSize, widgetSize / 1.0 );
        if(player->GetID() != LocalPlayer()->GetID())
        {
            widget->move( xOffset, yOffset );
            xOffset += widget->width() + xPadding;
        }
        else
        {
            widget->move( xPadding, height() - widget->height() - yOffset );
        }

        QGraphicsProxyWidget *proxy = boardScene->addWidget(widget);
        proxy->setZValue(1e29);
        proxy->setVisible(true);

        //view->repaint();
//        GraphicsWidget *proxy = new GraphicsWidget;
//        proxy->setWidget(widget);
//        proxy->setCacheMode(QGraphicsItem::ItemCoordinateCache);
//        proxy->setZValue(1e30); // Make sure the dialog is drawn on top of all other (OpenGL) items
//        proxy->setVisible(true);
//        boardScene->addItem(proxy);
    }
    setupCards();
    setupDice();
}

void ScreenGameBoard::setupCards()
{
    int xPadding = width() * 0.01;
    int yPadding = xPadding;
    playerHand = new PlayerHandWidget();
    playerHand->resize(width()*0.5,height()*0.2);
    playerHand->move(width()*0.5-playerHand->width()*0.5 , height() - playerHand->height() - yPadding );
    boardScene->addWidget(playerHand);
}

void ScreenGameBoard::setupDice()
{
    DiceDialog *dice = new DiceDialog();
    int xPadding =  width() * 0.01;
    int yPadding = xPadding;
    dice->resize(200,110);
    dice->move(width() - dice->width() , height() - dice->height() - yPadding  );
    boardScene->addWidget(dice);

}

ScreenGameBoard::~ScreenGameBoard()
{
}
