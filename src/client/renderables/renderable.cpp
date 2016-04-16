#include "renderable.h"
#include "client/util.h"

Renderable::Renderable(QObject *parent) :
    QObject(parent)
{
}

void Renderable::SetAngles(const QVector3D &angles)
{
    ang = angles;
    mat.setToIdentity();
    mat.translate( pos );
    mat.rotate(ang.x(), QVector3D(1.0,0.0,0.0));
    mat.rotate(ang.y(), QVector3D(0.0,0.0,1.0));
    mat.rotate(ang.z(), QVector3D(0.0,1.0,0.0));
}

void Renderable::SetPos(const QVector3D &t)
{
    pos = t;
    mat.setToIdentity();
    mat.translate( pos );
    mat.rotate(ang.x(), QVector3D(1.0,0.0,0.0));
    mat.rotate(ang.y(), QVector3D(0.0,0.0,1.0));
    mat.rotate(ang.z(), QVector3D(0.0,1.0,0.0));
}

void Renderable::Draw() const
{
    glPushMatrix();
    qMultMatrix(mat);

    draw();

    glPopMatrix();
}

void Renderable::buildGeometry() {}

void Renderable::draw() const {}
