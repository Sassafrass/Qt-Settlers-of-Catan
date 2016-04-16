#include <QVBoxLayout>
#include <QPalette>
#include "roomlistwidget.h"
#include "roomlabel.h"
#include <QDebug>

RoomListWidget::RoomListWidget(QWidget *parent) :
    QWidget(parent)
{

    selected = 0;

    QVBoxLayout *layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignTop);
        layout->setMargin(0);
        layout->setSpacing(0);
    setLayout(layout);

    setAutoFillBackground(true);

    QPalette pal(palette());
        pal.setColor(QPalette::Background, Qt::white);
    setPalette(pal);

    setSizePolicy(QSizePolicy::Expanding,
                  QSizePolicy::Expanding);
}

quint16 RoomListWidget::GetSelected() const
{
    if( selected )
        return selected->GetID();
    return 0;
}

void RoomListWidget::receivedRoomUpdate(QDataStream &msg)
{
    quint16 roomID;
    quint8 num_players;
    msg >> roomID;
    msg >> num_players;
    if( !rooms.contains( roomID ) )
        return;

    rooms[roomID]->SetNumPlayers(num_players);
}

void RoomListWidget::Clear()
{
    if( selected )
        emit selectionChanged(false);

    selected = 0;

    foreach( RoomLabel *room, rooms )
    {

        disconnect( room, SIGNAL(clicked()),
                    this, SLOT(roomSelected()));
        room->deleteLater();
    }
    rooms.clear();
}

void RoomListWidget::listDoubleClicked()
{
    emit doubleClicked();
}

void RoomListWidget::AddRoom(RoomLabel *room)
{
    if( rooms.contains( room->GetID() ) )
    {
        RemoveRoom(room->GetID());
    }

    connect( room, SIGNAL(clicked()),
             this, SLOT(roomSelected()));
    connect(room, SIGNAL(doubleClick()),
            this, SLOT(listDoubleClicked()));

    rooms[room->GetID()] = room;
    layout()->addWidget(room);
    adjustSize();
}

void RoomListWidget::RemoveRoom(quint16 roomID)
{
    if( !rooms.contains(roomID) )
        return;

    RoomLabel *room = rooms[roomID];

    disconnect( room, SIGNAL(clicked()),
                this, SLOT(roomSelected()));

    if( selected == room )
    {
        selected = 0;
        emit selectionChanged(false);
    }

    layout()->removeWidget(room);
    room->deleteLater();
    adjustSize();

    rooms.remove( roomID );
}

void RoomListWidget::roomSelected()
{

    RoomLabel *room = qobject_cast<RoomLabel*>(sender());
    if( !room )
    {
        if( selected )
        {
            selected->SetSelected(false);
            selected = 0;
            emit selectionChanged(false);
        }
    }
    else if( selected != room )
    {
        selected = room;
        room->SetSelected(true);
        emit selectionChanged(true);
    }
}

void RoomListWidget::mousePressEvent(QMouseEvent *)
{
    if( selected )
    {
        selected->SetSelected(false);
        selected = 0;
        emit selectionChanged(false);
    }
}
