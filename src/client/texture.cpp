/****************************************************************************
** **Settlers of Catan**
** Texture class
** author: Frank Sasto / Dore Weber
** date: 3/27/2012
**
** This class represents static functions for loading and binding textures
** for openGL.
****************************************************************************/

#include "client/texture.h"
#include <QImage>

QMap<TERRAIN::ENUM,GLuint> Texture::terrainMap;
QMap<TOKEN::ENUM,GLuint> Texture::tokenMap;

#define GL_BGRA 0x80E1

GLuint loadTexture(const QString &path)
{

    QImage image(path);

    if( image.isNull() )
        return 0;

    image = image.convertToFormat(QImage::Format_ARGB32);
    image = image.mirrored(true, false);

    GLuint texture = 0;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    // Works on x86, so probably works on all little-endian systems.
    // Does it work on big-endian systems?
    glTexImage2D(GL_TEXTURE_2D, 0, 4, image.width(), image.height(), 0,
        GL_BGRA, GL_UNSIGNED_BYTE, image.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

#define BIND_TERRAIN(e,name)\
Texture::terrainMap[e] = loadTexture(QString(":/textures/tiles/%1").arg(name))
#define BIND_TOKEN(e,name)\
Texture::tokenMap[e] = loadTexture(QString(":/textures/chits/%1").arg(name))

GLuint Texture::getTexture(const TERRAIN::ENUM &type)
{
    return Texture::terrainMap[type];
}

GLuint Texture::getTexture(const TOKEN::ENUM &type)
{
    return Texture::tokenMap[type];
}

void Texture::loadTextures()
{
    //load textures
    BIND_TERRAIN(TERRAIN::HILLS,        "clay");
    BIND_TERRAIN(TERRAIN::DESERT,       "desert");
    BIND_TERRAIN(TERRAIN::FIELDS,       "fields");
    BIND_TERRAIN(TERRAIN::FOREST,       "forest");
    BIND_TERRAIN(TERRAIN::MOUNTAINS,    "mountains");
    BIND_TERRAIN(TERRAIN::PASTURE,      "pasture");
    BIND_TERRAIN(TERRAIN::WATER,        "water");
    BIND_TERRAIN(TERRAIN::WATER_ANY,    "water_any");
    BIND_TERRAIN(TERRAIN::WATER_WOOL,   "water_wool");
    BIND_TERRAIN(TERRAIN::WATER_BRICK,  "water_brick");
    BIND_TERRAIN(TERRAIN::WATER_ORE,    "water_iron");
    BIND_TERRAIN(TERRAIN::WATER_WHEAT,  "water_wheat");
    BIND_TERRAIN(TERRAIN::WATER_WOOD,   "water_wood");
    BIND_TOKEN(TOKEN::TWO,      "chit1");
    BIND_TOKEN(TOKEN::THREE,    "chit2");
    BIND_TOKEN(TOKEN::FOUR,     "chit3");
    BIND_TOKEN(TOKEN::FIVE,     "chit4");
    BIND_TOKEN(TOKEN::SIX,      "chit5");
    BIND_TOKEN(TOKEN::EIGHT,    "chit6");
    BIND_TOKEN(TOKEN::NINE,     "chit7");
    BIND_TOKEN(TOKEN::TEN,      "chit8");
    BIND_TOKEN(TOKEN::ELEVEN,   "chit9");
    BIND_TOKEN(TOKEN::TWELVE,   "chit10");
}
