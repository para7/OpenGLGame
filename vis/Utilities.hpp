#pragma once

#include "GLincludes.h"
#include <array>

class GLEnableScope
{
private:

    const GLenum _mode;

public:

    explicit GLEnableScope(GLenum mode)
        : _mode(mode)
    {
        glEnable(_mode);
    }

    virtual ~GLEnableScope() final
    {
        glDisable(_mode);
    }
};


struct Color
{
    GLfloat color_array[4];
    GLfloat& r, &g, &b, &a;

    Color()
        : r(color_array[0])
        , g(color_array[1])
        , b(color_array[2])
        , a(color_array[3])
//        , color_array({ 0,0,0,0 })
    {
        r = g = b = a = 0;
    }

    Color(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _a)
        : r(color_array[0])
        , g(color_array[1])
        , b(color_array[2])
        , a(color_array[3])
//        , color_array({ _r, _g, _b, _a })
    {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }

    Color(GLfloat _r, GLfloat _g, GLfloat _b)
        : r(color_array[0])
        , g(color_array[1])
        , b(color_array[2])
        , a(color_array[3])
//        , color_array({ _r, _g, _b, 0})
    {
        r = _r;
        g = _g;
        b = _b;
        a = 0;
    }


    void operator=(const Color& _c)
    {
        this->r = _c.r;
        this->g = _c.g;
        this->b = _c.b;
        this->a = _c.a;
    }
};