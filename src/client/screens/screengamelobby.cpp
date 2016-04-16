#include <QIcon>
#include <QPixmap>
#include <QVBoxLayout>
#include <QTimer>
#include "client/widgets/playerreadywidget.h"
#include "client/managers/networkmanager.h"
#include "screengamelobby.h"
#include "ui_screengamelobby.h"
#include "client/enums/c_playercolor.h"
#include "client/widgets/playerreadywidget.h"
#include "client/entities/player.h"
#include "shared/defines.h"
#include "client/screens/screengameboard.h"

ScreenGameLobby::ScreenGameLobby(QWidget *parent, ScreenManager *manager, const QPoint &pos) :
    CatanScreen(parent, manager , pos),
    ui(new Ui::ScreenGameLobby)
{

    ui->setupUi(this);
    ui->PlayerArea->setLayout(new QVBoxLayout(ui->PlayerArea));
    ui->PlayerArea->layout()->setAlignment(Qt::AlignTop);
    ui->lcdTimer->setHidden(true);
    ui->buttonCanceled->setHidden(true);
    ui->progressBarStarting->setHidden(true);
    timer = new QTimer(this);

    // Enable when color works
    ui->labelColor->setHidden(true);

    // Connect all slots and signals to actions they need.
    connect(timer, SIGNAL(timeout()),
            this , SLOT(updateTimer()));
    disableGameOptions();
    connect(net::Connection, SIGNAL(receivedRoomPlayers(QDataStream&)),
            this ,SLOT(receivedRoomPlayers(QDataStream&)));
    connect(net::Connection, SIGNAL(receivedRoomUserJoined(QDataStream&)),
            this , SLOT(receivedRoomUserJoined(QDataStream&)));
    connect(net::Connection, SIGNAL(receivedRoomUserExited(QDataStream&)),
            this , SLOT(receivedRoomUserExited(QDataStream&)));
    connect(net::Connection, SIGNAL(receivedRoomNewHost(QDataStream&)),
            this, SLOT(receivedRoomNewHost(QDataStream&)));
    connect(net::Connection, SIGNAL(receivedRoomPlayerReady(QDataStream&)),
            this , SLOT(receivedRoomPlayerReady(QDataStream&)));
    connect(net::Connection, SIGNAL(receivedRoomStarting(QDataStream&)),
            this, SLOT(receivedRoomStarting()));
    connect(net::Connection, SIGNAL(receivedRoomStartingInterrupt(QDataStream&)),
            this, SLOT(receivedRoomStartingInterrupt(QDataStream&)));
    connect(ui->buttonStartGame, SIGNAL(clicked()),
            this, SLOT(sendStartGame()));
    connect(ui->buttonExit, SIGNAL(clicked()),
            this, SLOT(exitButtonPressed()));
    connect(ui->buttonCanceled, SIGNAL(clicked()),
            this, SLOT(cancelButtonPressed()));
    connect(net::Connection, SIGNAL(receivedRoomStart(QDataStream&)),
            this, SLOT(receivedRoomStart(QDataStream&)));
}

void ScreenGameLobby::receivedRoomStart(QDataStream &msg)
{
    quint16 gameSeed;
    msg >> gameSeed;

    quint8 numPlayers;
    msg >> numPlayers;

    QVector<CatanPlayer*> players = GetPlayerVector();

    for(int i = 0; i < numPlayers; i++)
    {
        quint8 playerID;
        quint8 colorID;
        QString playerName;
        msg >> playerID;
        msg >> colorID;
        msg >> playerName;
        CatanPlayer *player = getPlayer(playerID);
        if( !player ) //THIS IS A HACK
        {
            //create the player
            player = new CatanPlayer( playerID, playerName, this );
            players.push_back( player );
            if( !LocalPlayer() )
                CatanPlayer::localPlayer = player;
        }

        player->SetColor(static_cast<PlayerColor>(colorID));
    }

    ScreenGameBoard *boardScreen = qobject_cast<ScreenGameBoard*>(manager->GetScreen(SCREEN_NAME::GAMEBOARD));
    Q_ASSERT(boardScreen);

    boardScreen->GenerateBoard(gameSeed, numPlayers);
    boardScreen->SetPlayers(players);
    manager->ForceSetScreen(SCREEN_NAME::GAMEBOARD);

}

void ScreenGameLobby::disableGameOptions()
{
    ui->op_chits->setEnabled(false);
    ui->op_trade->setEnabled(false);
    ui->gameOptionsForm->setEnabled(false);
}

void ScreenGameLobby::Activated()
{

}

QVector<CatanPlayer *> ScreenGameLobby::GetPlayerVector()
{
    QVector<CatanPlayer*> playerVector;
    foreach(CatanPlayer *player, playerMap.keys())
    {
        playerVector.push_back(player);
    }
    return playerVector;
}

void ScreenGameLobby::Deactivated()
{
    foreach( CatanPlayer *player, playerMap.keys() )
    {
        player->deleteLater();
    }
    foreach( PlayerReadyWidget *widget, playerMap.values() )
    {
        widget->deleteLater();
    }
    disableGameOptions();
    playerMap.clear();
    readyMap.clear();
    LocalPlayer()->deleteLater();
}

CatanPlayer* ScreenGameLobby::getPlayer(int ID)
{
    foreach(CatanPlayer *p, playerMap.keys())
    {
        if (p->GetID() == ID )
            return p;
    }
    return 0;
}

void ScreenGameLobby::addPlayer( int ID, QString name , bool readyStatus)
{
    CatanPlayer* player = getPlayer( ID );
    if( player ) return; //we already have this player

    //create the player
    player = new CatanPlayer( ID, name, this );
    PlayerReadyWidget* playerWidget = new PlayerReadyWidget(player,this);
    playerMap[player] = playerWidget;

    playerWidget->SetReadyCheckBox(readyStatus);
    readyMap[player] = readyStatus;
    if(ui->PlayerArea->layout()->isEmpty())
    {
        CatanPlayer::localPlayer = player;
        playerWidget->SetController(true);
    }
    else
        playerWidget->SetController(false);
    ui->PlayerArea->layout()->addWidget(playerWidget);
    playerWidget->setParent(ui->PlayerArea);
}

void ScreenGameLobby::sendStartGame()
{
    net::Begin(NETWORK_COMMAND::PLAYER_START);
    net::Send();
}

void ScreenGameLobby::cancelButtonPressed()
{
    playerMap[LocalPlayer()]->SetReadyCheckBox(false);
}

void ScreenGameLobby::setHost( int ID )
{
    CatanPlayer* player = getPlayer( ID );
    if( !player )
    {
        hostID = 0;
        return;
    }
    hostID = player->GetID();
    playerMap[player]->SetHost(true);
}

void ScreenGameLobby::everyoneReady()
{
    foreach(bool ready, readyMap.values())
    {
        if(!ready)
        {
            ui->buttonStartGame->setEnabled(false);
            return;
        }
    }
    if(playerMap.size() >= CATAN_MIN_PLAYERS && hostID == LocalPlayer()->GetID())
    {
        ui->buttonStartGame->setEnabled(true);
    }
   }

void ScreenGameLobby::receivedRoomPlayerReady(QDataStream &msg)
{
    quint8 playerReady;
    bool readyStatus;

    msg >> playerReady;
    msg >> readyStatus;

    CatanPlayer* player = getPlayer(playerReady);
    if(!player) return;
    playerMap[player]->SetReadyCheckBox(readyStatus);
    readyMap[player] = readyStatus;
    everyoneReady();
}

void ScreenGameLobby::receivedRoomPlayers(QDataStream &msg)
{
    // get number of players
    quint8 numPlayer;
    msg >> numPlayer;

    // get host info
    quint8 hostID;
    QString hostName;
    bool hostReadyStatus;
    msg >> hostID;
    msg >> hostName;
    msg >> hostReadyStatus;
    addPlayer( hostID, hostName, hostReadyStatus);
    qDebug() << "setting host";
    setHost( hostID );

    quint8 playerID;
    QString playerName;
    bool playerReadyStatus;
    for(int i = 0 ; i < numPlayer - 1; i++)
    {
        msg >> playerID;
        msg >> playerName;
        msg >> playerReadyStatus;
        addPlayer( playerID, playerName, playerReadyStatus );
    }
    //TODO do someshit with this

    if(manager->IsCurrentScreen(SCREEN_NAME::CREATE_ROOM))
    {
        manager->SetScreen(SCREEN_NAME::READY_ROOM);
    }
    else if(manager->IsCurrentScreen(SCREEN_NAME::LOBBY))
    {
       manager->ForceSetScreen(SCREEN_NAME::READY_ROOM);
    }
}

void ScreenGameLobby::receivedRoomUserJoined(QDataStream &msg)
{
    quint16 lobbyID;
    quint8 ownID;
    QString ownName;

    msg >> lobbyID;
    msg >> ownID;
    msg >> ownName;
    addPlayer(ownID, ownName, false);
}


void ScreenGameLobby::receivedRoomUserExited(QDataStream &msg)
{
    //Get the player name
    quint8 exitedPlayerID;
    msg >> exitedPlayerID;
    CatanPlayer *exitedPlayer = getPlayer(exitedPlayerID);
    if(!exitedPlayer) return;
    playerMap.remove(exitedPlayer);
    readyMap.remove(exitedPlayer);
    exitedPlayer->deleteLater();
}

void ScreenGameLobby::exitButtonPressed()
{

    net::Begin(NETWORK_COMMAND::PLAYER_LEAVE);
    net::Send();
    manager->ForceSetScreen(SCREEN_NAME::MAIN_MENU );
}


void ScreenGameLobby::receivedRoomStarting()
{
    ui->labelGameStatus->setText("Starting Game!");
    ui->lcdTimer->display(CATAN_ROOM_START_TIME);
    startTime = QTime::currentTime().addSecs(CATAN_ROOM_START_TIME);
    timer->start(100);
}

void ScreenGameLobby::receivedRoomNewHost(QDataStream &msg)
{
    quint8 newHostID;
    msg >> newHostID;
    setHost(newHostID);
}

void ScreenGameLobby::receivedRoomStartingInterrupt(QDataStream &msg)
{
    quint8 playerID;
    msg >> playerID;
    CatanPlayer* player = getPlayer(playerID);
    timer->stop();

    if (!player) return;
    ui->labelGameStatus->setText(player->GetName() + "  Canceled");
    ui->lcdTimer->setHidden(true);
    ui->buttonCanceled->setHidden(true);
    ui->lcdTimer->display(5);
}

void ScreenGameLobby::updateTimer()
{
   ui->lcdTimer->setHidden(false);
   ui->buttonCanceled->setHidden(false);
   int remainingTime = qMax( QTime::currentTime().secsTo(startTime), 0 );
   ui->lcdTimer->display(remainingTime);
   int progressCompleted = static_cast<int>((QTime::currentTime().msecsTo(startTime)/startTime.msec()));
   //ui->progressBarStarting->value() = progressCompleted;
}

void ScreenGameLobby::moveToGameBoard()
{
    timer->stop();
    timer->deleteLater();
    manager->SetScreen(SCREEN_NAME::GAMEBOARD);
}

ScreenGameLobby::~ScreenGameLobby()
{
    delete ui;
}
