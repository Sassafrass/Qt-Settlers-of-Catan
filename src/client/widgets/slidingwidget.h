/****************************************************************************
** **Settlers of Catan**
** SlidingWidget
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** This is used so that all that all the screen will be able to slide to the main window
** This keeps the abstraction so that it is very easy to slide each screen.
**
** TODO:
** Make it so that we abmit the signal when the slidding is finisshed to make sure that
** We can't move tell it is send.
**
****************************************************************************/


#ifndef SLIDINGWIDGET_H
#define SLIDINGWIDGET_H

#include <QWidget>
#include <QPropertyAnimation>

class SlidingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SlidingWidget(QWidget *parent = 0);

    void SlideTo(QPoint targetPos, qreal speed); //speed in pixels / second
    void Center();
signals:
    void SlideFinished();
public slots:
    
private:
    QPropertyAnimation *slideAnim;
};

#endif // SLIDINGWIDGET_H
