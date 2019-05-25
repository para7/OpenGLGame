#pragma once
#include "GLincludes.h"

class Rectangle
{
public:

    GLdouble x, y, z, w, h;

    GLdouble rx, ry, rz;

public:
    Rectangle() {};

    Rectangle(GLdouble _x, GLdouble _y, GLdouble _z, GLdouble _w, GLdouble _h)
        : x(_x)
        , y(_y)
        , z(_z)
        , w(_w)
        , h(_h)
    {}

    Rectangle(GLdouble _x, GLdouble _y, GLdouble _z, GLdouble _w, GLdouble _h, GLdouble _rx, GLdouble _ry, GLdouble _rz)
        : x(_x)
        , y(_y)
        , z(_z)
        , w(_w)
        , h(_h)
        , rx(_rx)
        , ry(_ry)
        , rz(_rz)
    {}

    ~Rectangle() {};

    inline void Rotate(GLdouble _rx, GLdouble _ry, GLdouble _rz) noexcept
    {
        rx += _rx;
        ry += _ry;
        rz += _rz;
    }

    Rectangle Rotated(GLdouble _rx, GLdouble _ry, GLdouble _rz) const
    {
        Rectangle ret(*this);

        ret.Rotate(_rx, _ry, _rz);

        return ret;
    }

    void Moveby(GLdouble _x, GLdouble _y, GLdouble _z)
    {
        x += _x;
        y += _y;
        z += _z;
    }

    Rectangle Movedby(GLdouble _x, GLdouble _y, GLdouble _z) const
    {
        Rectangle ret(*this);

        ret.Moveby(_x, _y, _z);

        return ret;
    }


    void draw() const
    {
        static const GLdouble vertex_data[4][3] = { 1.0,  0.0,  1.0,
                                1.0,  0.0, -1.0,
                               -1.0,  0.0, -1.0,
                               -1.0,  0.0,  1.0 };

        static const GLdouble normal_data[4][3] = { 0.447214,  0.774597,  0.447214,
                                    0.447214,  0.774597, -0.447214,
                                   -0.447214,  0.774597, -0.447214,
                                   -0.447214,  0.774597,  0.447214 };
        int i;

        glPushMatrix();

        glTranslated(x, y, z);

        glRotated(rx, 1.0, 0, 0);
        glRotated(ry, 0, 1.0, 0);
        glRotated(rz, 0, 0, 1.0);

//        glScaled(1, 1, 1);

        glBegin(GL_POLYGON);
        for (i = 0; i < 4; ++i)
        {
            glNormal3dv(normal_data[i]);
            glVertex3dv(vertex_data[i]);
        }
        glEnd();

        glPopMatrix();
    }
};

