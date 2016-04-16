/****************************************************************************
** **Settlers of Catan**
** CatanScreen
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** This class is used so that our other screen and inherate from it. It inhetates
** SliddingScreen that screen has functions that that are used so that we can slide all over.
** If you want to make a screen it must inherate from this class.
**
****************************************************************************/

#ifndef CATANSCREEN_H
#define CATANSCREEN_H

#include <QWidget>

#include "client/widgets/slidingwidget.h"
#include "client/managers/screenmanager.h"

class CatanScreen : public SlidingWidget
{
    Q_OBJECT
public:
    explicit CatanScreen(QWidget *parent, ScreenManager *manager, const QPoint &pos);
    void SetPos(QPoint screenPos);
    void SetActive( bool );
    bool GetActive() const;
    QPoint GetPos() const;
    int x() const;
    int y() const;
public slots:
    virtual void keyPressEvent(QKeyEvent *);
protected:
    ScreenManager *manager;
    virtual void Activated();
    virtual void Deactivated();
private:
    QPoint screenPos;
    bool active;
};

#endif // CATANSCREEN_H
