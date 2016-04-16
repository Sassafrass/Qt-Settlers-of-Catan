/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
** This file has been modified by Frank Sasto to allow textured geometry.
** date: 3/27/2012
**
****************************************************************************/

#include "geometry.h"
#include "client/util.h"

void Geometry::loadArrays() const
{
    glVertexPointer(3, GL_FLOAT, 0, vertices.constData());
    glNormalPointer(GL_FLOAT, 0, normals.constData());
}

void Geometry::finalize()
{
    // TODO: add vertex buffer uploading here

    // Finish smoothing normals by ensuring accumulated normals are returned
    // to length 1.0.
    for (int i = 0; i < normals.count(); ++i)
        normals[i].normalize();
}

void Geometry::appendSmooth(const QVector3D &a, const QVector3D &n, int from)
{
    // Smooth normals are acheived by averaging the normals for faces meeting
    // at a point.  First find the point in geometry already generated
    // (working backwards, since most often the points shared are between faces
    // recently added).
    int v = vertices.count() - 1;
    for ( ; v >= from; --v)
        if (qFuzzyCompare(vertices[v], a))
            break;
    if (v < from)
    {
        // The vert was not found so add it as a new one, and initialize
        // its corresponding normal
        v = vertices.count();
        vertices.append(a);
        normals.append(n);
    }
    else
    {
        // Vert found, accumulate normals into corresponding normal slot.
        // Must call finalize once finished accumulating normals
        normals[v] += n;
    }
    // In both cases (found or not) reference the vert via its index
    faces.append(v);
}

void Geometry::appendFaceted(const QVector3D &a, const QVector3D &n)
{
    // Faceted normals are achieved by duplicating the vert for every
    // normal, so that faces meeting at a vert get a sharp edge.
    int v = vertices.count();
    vertices.append(a);
    normals.append(n);
    faces.append(v);
}

Patch::Patch(Geometry *g)
   : start(g->faces.count())
   , count(0)
   , initv(g->vertices.count())
   , sm(Patch::Smooth)
   , geom(g)
{
    qSetColor(faceColor, QColor(Qt::darkGray));
}

void Patch::rotate(qreal deg, QVector3D axis)
{
    mat.rotate(deg, axis);
}

void Patch::translate(const QVector3D &t)
{
    mat.translate(t);
}

//! [2]
void Patch::draw() const
{
    glPushMatrix();
    qMultMatrix(mat);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, faceColor);

    const GLushort *indices = geom->faces.constData();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, indices + start);
    glPopMatrix();
}
//! [2]

void Patch::addTri(const QVector3D &a, const QVector3D &b, const QVector3D &c, const QVector3D &n)
{
    QVector3D norm = n.isNull() ? QVector3D::normal(a, b, c) : n;
    if (sm == Smooth)
    {
        geom->appendSmooth(a, norm, initv);
        geom->appendSmooth(b, norm, initv);
        geom->appendSmooth(c, norm, initv);
    }
    else
    {
        geom->appendFaceted(a, norm);
        geom->appendFaceted(b, norm);
        geom->appendFaceted(c, norm);
    }
    count += 3;
}

void Patch::addQuad(const QVector3D &a, const QVector3D &b, const QVector3D &c, const QVector3D &d)
{
    QVector3D norm = QVector3D::normal(a, b, c);
    if (sm == Smooth)
    {
        addTri(a, b, c, norm);
        addTri(a, c, d, norm);
    }
    else
    {
        // If faceted share the two common verts
        addTri(a, b, c, norm);
        int k = geom->vertices.count();
        geom->appendSmooth(a, norm, k);
        geom->appendSmooth(c, norm, k);
        geom->appendFaceted(d, norm);
        count += 3;
    }
}

void TexGeometry::loadArrays() const
{
    glVertexPointer(3, GL_FLOAT, 0, vertices.constData());
    glNormalPointer(GL_FLOAT, 0, normals.constData());
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords.constData());
}

void TexGeometry::finalize()
{
    // TODO: add vertex buffer uploading here

    // Finish smoothing normals by ensuring accumulated normals are returned
    // to length 1.0.
    for (int i = 0; i < normals.count(); ++i)
        normals[i].normalize();
}

void TexGeometry::appendSmooth(const QVector3D &a, const QVector3D &n, const QVector2D &uv, int from)
{
    // Smooth normals are acheived by averaging the normals for faces meeting
    // at a point.  First find the point in geometry already generated
    // (working backwards, since most often the points shared are between faces
    // recently added).
    int v = vertices.count() - 1;
    for ( ; v >= from; --v)
        if (qFuzzyCompare(vertices[v], a))
            break;
    if (v < from)
    {
        // The vert was not found so add it as a new one, and initialize
        // its corresponding normal
        v = vertices.count();
        vertices.append(a);
        normals.append(n);
    }
    else
    {
        // Vert found, accumulate normals into corresponding normal slot.
        // Must call finalize once finished accumulating normals
        normals[v] += n;
    }
    // In both cases (found or not) reference the vert via its index
    faces.append(v);
    texCoords.append(uv);
}

void TexGeometry::appendFaceted(const QVector3D &a, const QVector3D &n, const QVector2D &uv)
{
    // Faceted normals are achieved by duplicating the vert for every
    // normal, so that faces meeting at a vert get a sharp edge.
    int v = vertices.count();
    vertices.append(a);
    normals.append(n);
    faces.append(v);
    texCoords.append(uv);
}



TexPatch::TexPatch(TexGeometry *g)
    : start(g->faces.count())
    , count(0)
    , initv(g->vertices.count())
    , sm(TexPatch::Faceted)
    , geom(g)
 {
     qSetColor(faceColor, QColor(Qt::darkGray));
 }

 void TexPatch::rotate(qreal deg, QVector3D axis)
 {
     mat.rotate(deg, axis);
 }

 void TexPatch::translate(const QVector3D &t)
 {
     mat.translate(t);
 }

 //! [2]
 void TexPatch::draw() const
 {
     glPushMatrix();
     qMultMatrix(mat);
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, faceColor);

     const GLushort *indices = geom->faces.constData();
     glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, indices + start);
     glPopMatrix();
 }
 //! [2]

 void TexPatch::addTri(const QVector3D &a, const QVector2D &auv,
                    const QVector3D &b, const QVector2D &buv,
                    const QVector3D &c, const QVector2D &cuv,
                    const QVector3D &n)
 {
     QVector3D norm = n.isNull() ? QVector3D::normal(a, b, c) : n;
     if (sm == Smooth)
     {
         geom->appendSmooth(a, norm, auv, initv);
         geom->appendSmooth(b, norm, buv, initv);
         geom->appendSmooth(c, norm, cuv, initv);
     }
     else
     {
         geom->appendFaceted(a, norm, auv);
         geom->appendFaceted(b, norm, buv);
         geom->appendFaceted(c, norm, cuv);
     }
     count += 3;
 }

 void TexPatch::addQuad(const QVector3D &a, const QVector2D &auv,
                     const QVector3D &b, const QVector2D &buv,
                     const QVector3D &c, const QVector2D &cuv,
                     const QVector3D &d, const QVector2D &duv)
 {
     QVector3D norm = QVector3D::normal(a, b, c);
     if (sm == Smooth)
     {
         addTri(a, auv, b, buv, c, cuv, norm);
         addTri(a, auv, c, cuv, d, duv, norm);
     }
     else
     {
         // If faceted share the two common verts
         addTri(a, auv, b, buv, c, cuv, norm);
         int k = geom->vertices.count();
         geom->appendSmooth(a, norm, auv, k);
         geom->appendSmooth(c, norm, cuv, k);
         geom->appendFaceted(d, norm, duv);
         count += 3;
     }
 }

Hexagon::Hexagon(TexGeometry *g, qreal side, qreal depth)
{
    QVector<QVector3D> outside;
    for (int i = 0; i < 6; i++) {
        qreal angle = (i * 2 * M_PI) / 6;
        outside << QVector3D(side * qCos(angle), side * qSin(angle), 0.0);
    }
    outside << QVector3D(side, 0.0, 0.0);
    QVector<QVector3D> out_back = extrude(outside, depth);
    QVector3D center = QVector3D(0.0, 0.0, 0.0);
    QVector3D normal = QVector3D(0.0, 0.0, 1.0);

    // Create front, back and sides as separate patches so that smooth normals
    // are generated for the curving sides, but a faceted edge is created between
    // sides and front/back

    TexPatch *os = new TexPatch(g);
    for (int i = 0; i < 6; ++i)
        os->addQuad(outside[(i + 1) % 6],    QVector2D(0.1,0.1),
                    outside[i],              QVector2D(0.0,0.1),
                    out_back[i],             QVector2D(0.0,0.0),
                    out_back[(i + 1) % 6],   QVector2D(0.1,0.0));

    TexPatch *fs = new TexPatch(g);
    for (int i = 0; i < 6; ++i) {
        qreal ang = (i * 2 * M_PI) / 6;
        qreal ang2 = ((i+1) * 2 * M_PI) / 6;
        fs->addTri( center,                 QVector2D(0.5,0.5),
                    outside[i],             QVector2D(qCos(ang)/2+0.5,qSin(ang)/2+0.5),
                    outside[(i + 1)],       QVector2D(qCos(ang2)/2+0.5,qSin(ang2)/2+0.5),
                    normal );
    }

    TexPatch *bs = new TexPatch(g);
    center.setZ(-depth);
    for (int i = 0; i < 6; ++i)
        bs->addTri( center,                 QVector2D(0.0,0.0),
                    out_back[(i + 1)],      QVector2D(0.0,0.0),
                    out_back[i],            QVector2D(0.0,0.0),
                    -normal );
    parts << os << fs << bs;

}

Cylinder::Cylinder(TexGeometry *g, qreal radius, int divisions, qreal depth)
{
    QVector<QVector3D> outside;
    for (int i = 0; i < divisions; i++) {
        qreal angle = (i * 2 * M_PI) / divisions;
        outside << QVector3D(radius * qCos(angle), radius * qSin(angle), 0.0);
    }
    outside << QVector3D(radius, 0.0, 0.0);
    QVector<QVector3D> out_back = extrude(outside, depth);
    QVector3D center = QVector3D(0.0, 0.0, 0.0);
    QVector3D normal = QVector3D(0.0, 0.0, 1.0);

    // Create front, back and sides as separate patches so that smooth normals
    // are generated for the curving sides, but a faceted edge is created between
    // sides and front/back

    TexPatch *os = new TexPatch(g);
    for (int i = 0; i < divisions; ++i)
        os->addQuad(outside[(i + 1) % divisions],    QVector2D(0.1,0.1),
                    outside[i],              QVector2D(0.0,0.1),
                    out_back[i],             QVector2D(0.0,0.0),
                    out_back[(i + 1) % divisions],   QVector2D(0.1,0.0));

    TexPatch *fs = new TexPatch(g);
    for (int i = 0; i < divisions; ++i) {
        qreal ang = (i * 2 * M_PI) / divisions;
        qreal ang2 = ((i+1) * 2 * M_PI) / divisions;
        fs->addTri( center,                 QVector2D(0.5,0.5),
                    outside[i],             QVector2D(qCos(ang)/2+0.5,qSin(ang)/2+0.5),
                    outside[(i + 1)],       QVector2D(qCos(ang2)/2+0.5,qSin(ang2)/2+0.5),
                    normal );
    }

    TexPatch *bs = new TexPatch(g);
    center.setZ(-depth);
    for (int i = 0; i < divisions; ++i)
        bs->addTri( center,                 QVector2D(0.0,0.0),
                    out_back[(i + 1)],      QVector2D(0.0,0.0),
                    out_back[i],            QVector2D(0.0,0.0),
                    -normal );
    parts << os << fs << bs;

}

RectPrism::RectPrism(Geometry *g, qreal width, qreal height, qreal depth)
{
    enum { bl, br, tr, tl };
    Patch *fb = new Patch(g);
    fb->setSmoothing(Patch::Faceted);

    // front face
    QVector<QVector3D> r(4);
    r[br].setX(width);
    r[tr].setX(width);
    r[tr].setY(height);
    r[tl].setY(height);
    QVector3D adjToCenter(-width / 2.0, -height / 2.0, depth / 2.0);
    for (int i = 0; i < 4; ++i)
        r[i] += adjToCenter;
    fb->addQuad(r[bl], r[br], r[tr], r[tl]);

    // back face
    QVector<QVector3D> s = extrude(r, depth);
    fb->addQuad(s[tl], s[tr], s[br], s[bl]);

    // side faces
    Patch *sides = new Patch(g);
    sides->setSmoothing(Patch::Faceted);
    sides->addQuad(s[bl], s[br], r[br], r[bl]);
    sides->addQuad(s[br], s[tr], r[tr], r[br]);
    sides->addQuad(s[tr], s[tl], r[tl], r[tr]);
    sides->addQuad(s[tl], s[bl], r[bl], r[tl]);

    parts << fb << sides;
}
