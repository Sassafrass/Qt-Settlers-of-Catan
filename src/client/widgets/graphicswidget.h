/****************************************************************************
** **Settlers of Catan**
** GraphicsWidget
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** I have no idea what this does
**
****************************************************************************/


#ifndef GRAPHICSWIDGET_H
#define GRAPHICSWIDGET_H

#include <QGraphicsProxyWidget>

class GraphicsWidget : public QGraphicsProxyWidget
{
public:
    GraphicsWidget() : QGraphicsProxyWidget(0, Qt::Window) {}
protected:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    virtual void resizeEvent(QGraphicsSceneResizeEvent *event);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // GRAPHICSWIDGET_H
