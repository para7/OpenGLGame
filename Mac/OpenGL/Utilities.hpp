#pragma once

#include "GLincludes.h"
#include <array>
#include "Vec23.hpp"
#include "DrawString.hpp"

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

}

constexpr double PI = 3.141592653589793238;