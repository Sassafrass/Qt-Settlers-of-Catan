#include "roomlabel.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QDebug>
#include <QPalette>
#include <QFont>

RoomLabel::RoomLabel(quint16 _roomID, QString _roomTitle, quint8 _numPlayers, quint8 _maxPlayers,
                     QWidget *parent) :
    QWidget(parent)
{
    roomID =_roomID;
    roomTitle = _roomTitle;
    maxPlayers = _maxPlayers;
    selected = false;
    QHBoxLayout *layout = new QHBoxLayout(this);

    QFont font = QFont("tahoma", 14, QFont::Bold);
    QLabel *roomNameLabel = new QLabel(roomTitle, this);
    roomNameLabel->setFont(font);
    QPalette pal(roomNameLabel->palette());
    pal.setColor( QPalette::Foreground, QColor("#333333"));
    roomNameLabel->setPalette(pal);
    layout->addWidget(roomNameLabel);
    playerCountLabel = new QLabel(this);
    playerCountLabel->setFont(font);
    playerCountLabel->setPalette(pal);
    layout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Fixed));
    layout->addWidget(playerCountLabel);

    SetNumPlayers(_numPlayers);

    setLayout(layout);

    setAutoFillBackground(true);
    adjustSize();

}

quint16 RoomLabel::GetID() const
{
    return roomID;
}

void RoomLabel::SetNumPlayers(quint8 playerCount)
{
    numPlayers = playerCount;
    //update player count display
    playerCountLabel->setText(
                tr("%0 / %1").arg(
                    QString::number(numPlayers),
                    QString::number(maxPlayers)
                    )
                );

}

void RoomLabel::SetSelected(bool bSelect)
{
    selected = bSelect;
    if( selected )
    {
        setAutoFillBackground(true);
        QPalette pal(palette());
        pal.setColor(QPalette::Background, QColor("#CCCCFF"));
        setPalette(pal);
    }
    else
    {
        setAutoFillBackground(false);
    }
}

void RoomLabel::enterEvent(QEvent *)
{
    if( selected ) return;

    setAutoFillBackground(true);
    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor("#DDDDFF"));
    setPalette(pal);
}

void RoomLabel::leaveEvent(QEvent *)
{
    if( selected ) return;

    setAutoFillBackground(false);
}

void RoomLabel::mouseDoubleClickEvent(QMouseEvent *)
{
    emit doubleClick();
}

void RoomLabel::mousePressEvent(QMouseEvent *)
{
    emit clicked();
}

RoomLabel::~RoomLabel()
{
    qDebug() << "Destructing room label";
}
