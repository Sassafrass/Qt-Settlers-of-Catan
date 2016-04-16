/****************************************************************************
** **Settlers of Catan**
** Base Entity Class
** author: Frank Sasto / Dore Weber
** date: 3/27/2012
**
** This is the base entity class for all drawable entities.
** An entity has a position and angle in world space coordinates.
****************************************************************************/

#ifndef BASE_H
#define BASE_H

#include <QObject>

class Entity : public QObject
{
    Q_OBJECT
public:
    explicit Entity(QObject *parent = 0);
    /**
     * Sets the parent entity.
     * @param Vector3D parent
     **/
    void SetParent(Entity &parent);

    /**
     * Gets parent.
     **/
    Entity* GetParent();
    
signals:
    
public slots:
protected:
private:
    Entity *parentEnt;
    
};

#endif // BASE_H
