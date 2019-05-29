#pragma once

#include "GLincludes.h"
#include <array>

namespace Utils
{

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
        union
        {
            GLfloat color_array[4];

            struct
            {
                GLfloat r;
                GLfloat g;
                GLfloat b;
                GLfloat a;
            };
        };

        Color()
        {
            r = g = b = a = 0;
        }

        Color(GLfloat _r, GLfloat _g, GLfloat _b, GLfloat _a)
        {
            r = _r;
            g = _g;
            b = _b;
            a = _a;
        }

        Color(GLfloat _r, GLfloat _g, GLfloat _b)
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


    template <class T>
    struct vector2d
    {
        T x, y;

        constexpr vector2d() : x(0), y(0) {};

        constexpr vector2d(const T& _x, const T& _y)
            : x(_x)
            , y(_y)
        {}

        vector2d movedBy(T& _x, T& _y) const
        {
            vector2d ret = vector2d(*this);
            ret.x += _x;
            ret.y += _y;
            return ret;
        }

        vector2d movedBy(const vector2d& v) const
        {
            vector2d ret = vector2d(*this);
            ret.x += v.x;
            ret.y += v.y;
            return ret;
        }
    };

    using Vec2f = vector2d<GLfloat>;
    using Vec2 = vector2d<GLdouble>;
    using Point = vector2d<int>;

    template <class T>
    struct vector3d
    {
        T x, y, z;

        constexpr vector3d() : x(0), y(0), z(0) {};

        constexpr vector3d(T _x, T _y, T _z)
            : x(_x)
            , y(_y)
            , z(_z)
        {}
    };
    using Vec3f = vector3d<GLfloat>;
    using Vec3 = vector3d<GLdouble>;

    //https://cpplover.blogspot.com/2014/10/c14-constexpr.html
    // C++11のconstexpr関数によるsqrtの実装
    template < typename T >
    constexpr T sqrt_aux(T s, T x, T prev)
    {
        return x != prev ?
            sqrt_aux(s, (x + s / x) / 2.0, x) : x;
    }

    template < typename T >
    constexpr T sqrt(T s)
    {
        T x = s / 2.0;
        T prev = 0.0;

        while (x != prev)
        {
            prev = x;
            x = (x + s / x) / 2.0;
        }
        return x;
    }

    template <typename T>
    constexpr T pow2(T a)
    {
        return a * a; 
    }

    //http://slis.tsukuba.ac.jp/~fujisawa.makoto.fu/lecture/iml/text/screen_character.html
    static void DrawString(std::string str, int w, int h, int x0, int y0)
    {
        glDisable(GL_LIGHTING);
        // 平行投影にする
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, w, h, 0);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        // 画面上にテキスト描画
        glRasterPos2f(x0, y0);
        int size = (int)str.size();
        for (int i = 0; i < size; ++i)
        {
            char ic = str[i];
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ic);
        }

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    }
}

constexpr double PI = 3.141592653589793238;