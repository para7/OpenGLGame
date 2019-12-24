#pragma once

#include "GLincludes.h"

namespace Utils
{
    template <class T>
    struct vector2d
    {
        T x, y;

        constexpr vector2d()
            : x(0)
            , y(0){};

        constexpr vector2d(const T& _x, const T& _y)
            : x(_x)
            , y(_y)
        {
        }

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

        constexpr vector3d()
            : x(0)
            , y(0)
            , z(0){};

        constexpr vector3d(T _x, T _y, T _z)
            : x(_x)
            , y(_y)
            , z(_z)
        {
        }
    };
    using Vec3f = vector3d<GLfloat>;
    using Vec3 = vector3d<GLdouble>;

}  // namespace Utils