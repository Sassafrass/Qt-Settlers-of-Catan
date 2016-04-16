/****************************************************************************
** **Settlers of Catan**
** Renderable
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** This is used to render the board and uses the chit and tile this is used just
** to make it viewable. This is used in the board screen and is very beutiful.
**
****************************************************************************/


#ifndef RENDERABLEENTITY_H
#define RENDERABLEENTITY_H

#include <QObject>
#include <QMatrix4x4>
#include <QVector3D>
#include "client/texture.h"

class Renderable : public QObject
{
    Q_OBJECT
public:
    explicit Renderable(QObject *parent);

    /**
     * Sets the position of the entity.
     * Translates the transformation matrix
     * @param Vector3D position
     **/
    void SetPos(const QVector3D &pos);

    /**
     * Sets the angles of the entity.
     * Rotates the transformation matrix
     * @param Vector3D angles (x = pitch, y = yaw, z = roll)
     **/
    void SetAngles(const QVector3D &angles);

    /**
     * Called to draw an object.
     * Pushes the entity's transformation matrix,
     * then calls the private draw method, then pops
     * the transformation matrix.
     **/
    void Draw() const;
signals:
    
public slots:
protected:
    /**
     * Builds the geometry of the object
     **/
    virtual void buildGeometry();
    /**
     * Draws the geometry of the object
     **/
    virtual void draw() const;


    QVector3D pos; //position
    QVector3D ang; //angles
    QMatrix4x4 mat; //transformation matrix
    
};

#endif // RENDERABLEENTITY_H
