
#include <QtOpenGL>

#include "boardscene.h"
#include "shared/entities/board.h"
#include "client/unitconvert.h"
#include "client/renderables/r_tile.h"
#include "client/renderables/r_road.h"
#include "client/entities/player.h"
#include "shared/entities/tile.h"
#include "shared/entities/edge.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

CatanBoardScene::CatanBoardScene(QWidget *parent)
    : QGraphicsScene(parent)
{
    setYRotation(-90);
    setXRotation(0);

    Texture::loadTextures();

    m_timer = new QTimer(this);
    m_timer->setInterval(20);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start();

    ghostPiece = 0;
}

void CatanBoardScene::SetBoard(CatanBoard *board)
{
    qDeleteAll(renderables);
    renderables.clear();

    this->board = board;

    foreach( CatanTile *tile, board->GetTiles() )
    {
        renderables.push_back(new RenderableTile(tile));
    }

    CatanTile *temp = new CatanTile(board);
    temp->SetTerrain( TERRAIN::DESERT );
    Q_ASSERT(LocalPlayer());
    ghostPiece = new RenderableRoad(LocalPlayer());
    ghostPiece->SetPos(QVector3D( 0, 0, 1 ));
}

static void qNormalizeAngle(qreal &angle)
{
    while (angle < 0)
        angle += 360;
    while (angle > 360)
        angle -= 360;
}

static void qClampAngle(qreal &angle)
{
    if (angle < 1)
        angle = 1;
    else if (angle > 360)
        angle = 360;
}

void CatanBoardScene::setXRotation(qreal angle)
{
    qClampAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        update();
    }
}

void CatanBoardScene::setYRotation(qreal angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        update();
    }
}

void
gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
   GLdouble xmin, xmax, ymin, ymax;

   ymax = zNear * tan(fovy * M_PI / 360.0);
   ymin = -ymax;
   xmin = ymin * aspect;
   xmax = ymax * aspect;

   glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
}

/**
 * normalize
 *   normalizes a 3d vector
 * @param GLFloat v[3] //3 dimensional array representing
 *   a vector3
 **/
void normalize(GLfloat v[3])
{
    GLfloat len = qSqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
    v[0] /= len;
    v[1] /= len;
    v[2] /= len;
}

/**
 * cross
 *   computes the cross product of 2 3d vectors.
 * @param GLfloat a[3] //3 dim array of a vector3
 * @param GLfloat b[3] //3 dim array of a vector3
 * @param GLfloat c[3] //resulting vector of a cross b
**/
void cross(const GLfloat a[3], const GLfloat b[3], GLfloat c[3])
{
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
}

/**
 * Camera utilty computes and translates the
 * worldspace coordinate system based on
 * camera position and direction
 **/
void
CatanBoardScene::gluLookAt(GLdouble eyex, GLdouble eyey, GLdouble eyez, GLdouble centerx,
     GLdouble centery, GLdouble centerz, GLdouble upx, GLdouble upy,
     GLdouble upz)
{
    GLfloat forward[3], side[3], up[3];

    forward[0] = centerx - eyex;
    forward[1] = centery - eyey;
    forward[2] = centerz - eyez;

    up[0] = upx;
    up[1] = upy;
    up[2] = upz;
    normalize(forward);

    /* Side = forward x up */
    cross(forward, up, side);
    normalize(side);

    /* Recompute up as: up = side x forward */
    cross(side, forward, up);

    //matrix transformation
    projMat.setRow(0, QVector4D(side[0], side[1], side[2], 0.0));
    projMat.setRow(1, QVector4D(up[0], up[1], up[2], 0.0));
    projMat.setRow(2, QVector4D(-forward[0], -forward[1], -forward[2], 0.0));
    projMat.setRow(3, QVector4D(0, 0, 0, 1));

    glMultMatrixd(projMat.constData());
    glTranslated(-eyex, -eyey, -eyez);

}

double fs_fmod(double x, double y)
{
    double a, b;
    const double c = x;

    if (0 > c) {
    x = -x;
    }
    if (0 > y) {
    y = -y;
    }
    if (y != 0 && DBL_MAX >= y && DBL_MAX >= x) {
    while (x >= y) {
    a = x / 2;
    b = y;
    while (a >= b) {
    b *= 2;
    }
    x -= b;
    }
    } else {
    x = 0;
    }
    return 0 > c ? -x : x;
}

void CatanBoardScene::drawBackground(QPainter *painter, const QRectF &)
{

    float width = float(painter->device()->width());
    float height = float(painter->device()->height());

    painter->beginNativePainting();

    glClearColor(78.0f/255.0f,
                 78.0f/255.0f,
                 127.0f/255.0f,
                 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);
    static GLfloat Ambient[4]= {0.5f, 0.5f, 0.5f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
    static GLfloat lightPosition[4] = { 0.5, 1.0, 9.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // select the projection matrix and clear it out
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    GLdouble fov = 30.0; //field of view in degrees
    GLdouble aspectRatio = (GLdouble)width/(GLdouble)height;
    GLdouble znear = 0.5;
    GLdouble zfar = 18.0;

    // set up an orthographic projection with the same near clip plane
    gluPerspective(fov, aspectRatio, znear, zfar);

    // select modelview matrix and clear it out
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    static const QVector3D camLookAt( 0.0, 0.0, 0.0 );
    static const QVector3D camUp( 0.0, 0.0, 1.0 );

    //set camera position
    camPos.setX( qCos(d2r(yRot)) * 3 * xRot / 180 );
    camPos.setY( qSin(d2r(yRot)) * 3 * xRot / 180 );
    camPos.setZ( 6 );

    //transform based on camera
    gluLookAt( camPos.x(),      camPos.y(),     camPos.z(),
               camLookAt.x(),   camLookAt.y(),  camLookAt.z(),
               camUp.x(),       camUp.y(),      camUp.z());

    //Get screen ray
    QVector3D forward = camLookAt - camPos;
    forward.normalize();

    // Side = forward x up
    QVector3D right = QVector3D::crossProduct(forward, camUp);
    right.normalize();

    // Recompute up as: up = side x forward
    QVector3D up = QVector3D::crossProduct(right, forward);

    QVector3D h = QVector3D::crossProduct( forward, up );
    h.normalize();

    QVector3D v = QVector3D::crossProduct( h, forward );
    v.normalize();

    qreal rad = d2r(fov);
    qreal vLength = qTan( rad / 2 ) * znear;
    qreal hLength = vLength * (qreal)width / height;

    v *= vLength;
    h *= hLength;

    qreal mx = (2 * lastCursorPos.x() / width - 1) * 2;
    qreal my = (1 - 2 * lastCursorPos.y() / height) * 2;

    QVector3D rayDest = camPos + forward + h*mx + v*my;
    QVector3D rayNormal = rayDest - camPos;
    rayNormal.normalize();

    QVector3D planeOrigin = QVector3D(0.0, 0.0, 0.0);
    QVector3D planeNormal = QVector3D(0.0, 0.0, 1.0);

    //Get board intersection
    qreal dotLineAndPlane = QVector3D::dotProduct( planeNormal, rayNormal );
    if( !qFuzzyIsNull(float(dotLineAndPlane)) )
    {
        qreal t =QVector3D::dotProduct( planeOrigin - rayDest, planeNormal ) / dotLineAndPlane;
        if( ghostPiece )
        {
            QVector3D worldPos = rayDest + rayNormal * t;
            QPoint edgePos = UnitConvert::WorldToEdge( worldPos );
            CatanTileEdge *edge = board->GetEdgeAt(edgePos.x(), edgePos.y());
            if( edge )
            {
                QVector3D ghostPos = UnitConvert::EdgeToWorld( edgePos.x(), edgePos.y() ) + QVector3D(0.0,0.0,0.01);
                ghostPiece->SetPos( ghostPos );
                ghostPiece->SetAngles( QVector3D( 0, edge->GetYaw(), 0) );
                //ghostPiece->SetPos( worldPos + QVector3D( 0.0, 0.0, +0.01 ) );
                ghostPiece->Draw();
    //            qDebug() << "tileX: " << tilePos.x() << "\t tileY: " << tilePos.y() <<
    //                        "\t ghostX: " << ghostPos.x() << "\t ghostY: " << ghostPos.y() <<
    //                        "\t worldX: " << worldPos.x() << "\t worldY: " << worldPos.y();
            }
        }
    }

    foreach( Renderable *r, renderables )
    {
        r->Draw();
    }

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    //glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHT0);
    glDisable(GL_NORMALIZE);

    painter->endNativePainting();
}

void CatanBoardScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    if (event->isAccepted())
        return;

    lastCursorPos = event->scenePos();
    event->accept();
}

void CatanBoardScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    if (event->isAccepted())
        return;

    qreal dx = event->scenePos().x() - lastCursorPos.x();
    qreal dy = event->scenePos().y() - lastCursorPos.y();

    if (event->buttons() & Qt::LeftButton) {
        //setXRotation(xRot + 16 * dy);
        setYRotation(yRot + dx / 8);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + dy);
    }
    lastCursorPos = event->scenePos();
    event->accept();
}
