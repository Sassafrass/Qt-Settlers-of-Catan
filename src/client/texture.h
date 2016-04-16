/****************************************************************************
** **Settlers of Catan**
** Texture class
** author: Frank Sasto / Dore Weber
** date: 3/27/2012
**
** This class represents static functions for loading and binding textures
** for openGL.
****************************************************************************/

#ifndef TEXTURE_H
#define TEXTURE_H

#include <QObject>
#include <QGLWidget>
#include <QMap>

#include "shared/enums/terrain.h"
#include "shared/enums/token.h"

class Texture : public QObject
{
    Q_OBJECT
public:
    static void loadTextures();
    static GLuint getTexture(const TERRAIN::ENUM &type);
    static GLuint getTexture(const TOKEN::ENUM &type);
signals:

public slots:
private:
    static QMap<TERRAIN::ENUM,GLuint> terrainMap;
    static QMap<TOKEN::ENUM,GLuint> tokenMap;
};

#endif // TEXTURE_H
