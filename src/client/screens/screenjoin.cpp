#include<QKeyEvent>

#include "screenjoin.h"
#include "ui_screenjoin.h"
#include "client/managers/networkmanager.h"
#include "shared/qout.h"
#include "client/widgets/roomlistwidget.h"

ScreenJoin::ScreenJoin(QWidget *parent, ScreenManager *manager, const QPoint &pos) :
    CatanScreen(parent, manager , pos),
    ui(new Ui::ScreenJoin)
{
    ui->setupUi(this);

    connect( ui->buttonBack, SIGNAL(clicked()),
             this, SLOT(gotoMenuScreen()));
    connect( ui->buttonRefreshList, SIGNAL(clicked()),
             this, SLOT(refreshRoomList()));
    connect(ui->buttonJoin, SIGNAL(clicked()),
            this, SLOT(joinButtonPressed()));
    roomList = new RoomListWidget(this);
    ui->roomList->setWidget(roomList);
    connect(roomList , SIGNAL(selectionChanged(bool)),
            this , SLOT(setCurrentSelected(bool)));
    connect(roomList , SIGNAL(doubleClicked()),
            this , SLOT(joinButtonPressed()));

    this->setFocusPolicy(Qt::StrongFocus);

}

void ScreenJoin::receivedRoomList(QDataStream &msg)
{

    quint16 count;
    msg >> count;

    LOG_DEBUG( "Receieved " << count << " rooms" << endl );
    roomList->Clear();

    for( int i = 0; i < count; i++ )
    {
        quint16 roomID = 0;
        QString roomTitle = "";
        quint8 numPlayers = 0;
        quint8 maxPlayers = 0;

        msg >> roomID;
        msg >> roomTitle;
        msg >> numPlayers;
        msg >> maxPlayers;
        roomList->AddRoom(new RoomLabel(roomID, roomTitle, numPlayers, maxPlayers));
    }
}
void ScreenJoin::keyPressEvent(QKeyEvent *p_event)
{
    if( !GetActive() ) return;
    if(p_event->key() == Qt::Key_Left || p_event->key() == Qt::Key_A)
    {
        gotoMenuScreen();
    }
}

void ScreenJoin::setCurrentSelected(bool isSelected)
{
    ui->buttonJoin->setEnabled(isSelected);
}

void ScreenJoin::joinButtonPressed()
{
    net::Begin(NETWORK_COMMAND::CLIENT_JOIN);
        net::AddShort(roomList->GetSelected());
    net::Send();
}

void ScreenJoin::receivedRoomClose(QDataStream &msg)
{
    quint16 roomID;
    msg >> roomID;
    roomList->RemoveRoom(roomID);
}

void ScreenJoin::receivedRoomNew(QDataStream &msg)
{
    quint16 roomID;
    QString roomName;
    quint8 maxPlayers;
    msg >> roomID;
    msg >> roomName;
    msg >> maxPlayers;
    roomList->AddRoom(new RoomLabel(roomID, roomName, 1, maxPlayers));
}

void ScreenJoin::Activated()
{

    connect( net::Connection, SIGNAL(receivedRoomList(QDataStream&)),
             this, SLOT(receivedRoomList(QDataStream&)));
    connect( net::Connection, SIGNAL(receivedRoomClose(QDataStream&)),
             this, SLOT(receivedRoomClose(QDataStream&)));
    connect( net::Connection, SIGNAL(receivedRoomNew(QDataStream&)),
             this, SLOT(receivedRoomNew(QDataStream&)));
    connect( net::Connection, SIGNAL(receivedRoomUpdate(QDataStream&)),
             roomList, SLOT(receivedRoomUpdate(QDataStream&)));

    net::Begin(NETWORK_COMMAND::CLIENT_LIST);
    net::Send();
}



void ScreenJoin::refreshRoomList()
{
    net::Begin(NETWORK_COMMAND::CLIENT_LIST);
    net::Send();
}

void ScreenJoin::Deactivated()
{
    disconnect( net::Connection, SIGNAL(receivedRoomList(QDataStream&)),
             this, SLOT(receivedRoomList(QDataStream&)));
    disconnect( net::Connection, SIGNAL(receivedRoomClose(QDataStream&)),
             this, SLOT(receivedRoomClose(QDataStream&)));
    disconnect( net::Connection, SIGNAL(receivedRoomNew(QDataStream&)),
             this, SLOT(receivedRoomNew(QDataStream&)));
    disconnect( net::Connection, SIGNAL(receivedRoomUpdate(QDataStream&)),
             roomList, SLOT(receivedRoomUpdate(QDataStream&)));
}

void ScreenJoin::gotoMenuScreen()
{
    manager->SetScreen(SCREEN_NAME::MAIN_MENU);
}

ScreenJoin::~ScreenJoin()
{
    delete ui;
}
