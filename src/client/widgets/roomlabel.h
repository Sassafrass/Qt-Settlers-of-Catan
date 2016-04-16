/****************************************************************************
** **Settlers of Catan**
** RoomLabel
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** This is used in the room list widget and keeps track of games in the RoomListWidget
** This was made to add functionality to the normal list box.
**
**
****************************************************************************/


#ifndef ROOMLABEL_H
#define ROOMLABEL_H

#include <QWidget>

class QLabel;

class RoomLabel : public QWidget
{
    Q_OBJECT
public:
    explicit RoomLabel(quint16 id, QString title, quint8 numPlayers,
                       quint8 maxPlayers, QWidget *parent = 0);
    virtual ~RoomLabel();
    void SetNumPlayers(quint8 playerCount);
    void SetSelected(bool selected);
    quint16 GetID() const;
signals:
    void doubleClick();
    void clicked();
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);
public slots:
private:
    quint16 roomID;
    QString roomTitle;
    quint8 numPlayers;
    quint8 maxPlayers;
    QLabel *playerCountLabel;
    bool selected;
};

#endif // ROOMLABEL_H
