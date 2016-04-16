/****************************************************************************
** **Settlers of Catan**
** GraphicsView
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** This class is used so that we can render the board as a widget.
** This was used in the ScreenGameBoard
**
****************************************************************************/


#ifndef CATANBOARDVIEWER_H
#define CATANBOARDVIEWER_H

#include <QGLWidget>
#include <QVector3D>
#include <QMatrix4x4>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QResizeEvent>

class CatanBoard;
class Renderable;

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QWidget *parent) : QGraphicsView(parent)
    {
        setWindowTitle(tr("3D Model Viewer"));
        setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    }

protected:
    void resizeEvent(QResizeEvent *event) {
        if (scene())
            scene()->setSceneRect(
                QRect(QPoint(0, 0), event->size()));
        QGraphicsView::resizeEvent(event);
    }
};

class CatanBoardScene : public QGraphicsScene
{
    Q_OBJECT
public:
    CatanBoardScene(QWidget *parent);
    void SetBoard(CatanBoard *board);
public slots:
    void setXRotation(qreal angle);
    void setYRotation(qreal angle);

signals:
protected:
    void drawBackground(QPainter *painter, const QRectF &);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
private:
    void gluLookAt(GLdouble eyex, GLdouble eyey, GLdouble eyez, GLdouble centerx,
         GLdouble centery, GLdouble centerz, GLdouble upx, GLdouble upy,
         GLdouble upz);
private:
    qreal xRot;
    qreal yRot;
    QPointF lastCursorPos;
    QVector3D camPos;
    QMatrix4x4 projMat;
    CatanBoard *board;
    QList<Renderable*> renderables;
    Renderable* ghostPiece;
    QTimer *m_timer;
};

#endif // CATANBOARDVIEWER_H
