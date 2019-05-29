#pragma once
#include "GLincludes.h"
#include "Utilities.hpp"
#include <algorithm>

class Rectangle
{
private:

    GLdouble normal_data[4][3];

public:

    void SetShader(float vertical, float side)
    {
        //       nxz = 1, ny = 1.4;
        float len = Utils::sqrt(Utils::pow2(side) + Utils::pow2(vertical) + Utils::pow2(side));

        float hoge[3] = { side / len, vertical / len, side / len };

        constexpr float sign[4][3] =
        {
           1, 1, 1,
           1, 1, -1,
           -1, 1, -1,
           -1, 1, 1,
        };

        for (int x = 0; x < 4; ++x)
        {
            for (int y = 0; y < 3; ++y)
            {
                normal_data[x][y] = hoge[y] * sign[x][y];
            }
        }
    }

    GLdouble x, y, z, w, h;

    GLdouble rx, ry, rz;

    Utils::Color color;

    float shader;

public:

    Rectangle()
    {
        SetShader(2.4, 1);
    };

    Rectangle(GLdouble _x, GLdouble _y, GLdouble _z, GLdouble _w, GLdouble _h)
        : x(_x)
        , y(_y)
        , z(_z)
        , w(_w)
        , h(_h)
    {
        SetShader(2.4, 1);
    }

    Rectangle(GLdouble _x, GLdouble _y, GLdouble _z, GLdouble _w, GLdouble _h, GLdouble _rx, GLdouble _ry, GLdouble _rz)
        : x(_x)
        , y(_y)
        , z(_z)
        , w(_w)
        , h(_h)
        , rx(_rx)
        , ry(_ry)
        , rz(_rz)
    {
        SetShader(2.4, 1);
    }

    ~Rectangle() {};

    inline void SetRotate(GLdouble _rx, GLdouble _ry, GLdouble _rz) noexcept
    {
        rx = _rx;
        ry = _ry;
        rz = _rz;
    }

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
        static const GLdouble vertex_data[4][3] =
        {
            0.5 ,  0.0,  0.5,
            0.5 ,  0.0, -0.5,
            -0.5,  0.0, -0.5,
            -0.5,  0.0,  0.5
        };

        int i;

        glPushMatrix();
        //ˆÚ“®
        glTranslated(x, y, z);
        //‰ñ“]
        glRotated(rx, 1.0, 0, 0);
        glRotated(ry, 0, 1.0, 0);
        glRotated(rz, 0, 0, 1.0);
        //•ÏŒ`
        glScaled(w, 0, h);

        //’…F
        //glMaterialfv(GL_FRONT, GL_DIFFUSE, color.color_array);
        glColor3fv(color.color_array);

        //VBO‚ðŽg‚Á‚Ä‚Ý‚½‚¢‚ªŽžŠÔ‚ª‚È‚¢

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

