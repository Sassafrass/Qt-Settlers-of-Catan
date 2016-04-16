/****************************************************************************
** **Settlers of Catan**
** util.h
** author: Frank Sasto / Dore Weber
** date: 3/27/2012
**
** This namespace provides utility functions for math operations such as
** matrix multiplication and degrees to radians
****************************************************************************/

#ifndef UTIL_H
#define UTIL_H

#include <QtOpenGL>
#include "shared/sh_util.h"

static inline void qMultMatrix(const QMatrix4x4 &mat)
{
    if (sizeof(qreal) == sizeof(GLfloat))
        glMultMatrixf((GLfloat*)mat.constData());
#ifndef QT_OPENGL_ES
    else if (sizeof(qreal) == sizeof(GLdouble))
        glMultMatrixd((GLdouble*)mat.constData());
#endif
    else
    {
        GLfloat fmat[16];
        qreal const *r = mat.constData();
        for (int i = 0; i < 16; ++i)
            fmat[i] = r[i];
        glMultMatrixf(fmat);
    }
}

#endif // UTIL_H
