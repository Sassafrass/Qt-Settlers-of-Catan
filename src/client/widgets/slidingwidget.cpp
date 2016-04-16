#include <QtCore/qmath.h>
#include "slidingwidget.h"
#include "shared/qout.h"

SlidingWidget::SlidingWidget(QWidget *parent) :
    QWidget(parent)
{
    slideAnim = new QPropertyAnimation(this, "pos");
    slideAnim->setEasingCurve(QEasingCurve::InOutQuad);

    connect( slideAnim, SIGNAL(finished()),
             this, SIGNAL(SlideFinished()));
}

void SlidingWidget::SlideTo(QPoint targetPos, qreal speed)
{
    slideAnim->stop();
    QPoint currentPos = geometry().topLeft();
    qreal distance = qSqrt(qPow(targetPos.x() - currentPos.x(), 2) +
                           qPow(targetPos.y() - currentPos.y(), 2));
    qreal time = distance / speed;
    slideAnim->setDuration(time*1000);
    slideAnim->setStartValue(currentPos);
    slideAnim->setEndValue(targetPos);
    slideAnim->start();
}

void SlidingWidget::Center()
{
    if( !parentWidget() )
    {
        LOG_ERROR("No parent!!!!" << endl);
        return;
    }
    QRect localGeometry( 0, 0, parentWidget()->width(), parentWidget()->height() );
    move( localGeometry.center() - QRect(0, 0, width(), height()).center() );
}
