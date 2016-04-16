/****************************************************************************
** **Settlers of Catan**
** RoomListWidget
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** This is used in ScreenJoin to make it so that we can highlight and keep track
** Of the currently selected screen to join.
**
**
****************************************************************************/


#ifndef ROOMLISTWIDGET_H
#define ROOMLISTWIDGET_H

#include <QWidget>
#include <QMap>
#include <QDataStream>

class RoomLabel;
class RoomListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RoomListWidget(QWidget *parent = 0);
    void Clear();
    void AddRoom( RoomLabel *room );
    void RemoveRoom( quint16 roomID );
    quint16 GetSelected() const;
signals:
    void selectionChanged(bool);
    void doubleClicked();
protected:
    virtual void mousePressEvent(QMouseEvent *);
public slots:
    void listDoubleClicked();
    void receivedRoomUpdate(QDataStream&);
private slots:
    void roomSelected();
private:
    RoomLabel *selected;
    QMap<quint16, RoomLabel*> rooms;
};

#endif // ROOMLISTWIDGET_H
