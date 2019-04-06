//
// vector2d.hpp
// jackbengine
//
// Created by Damien Bendejacq on 10/09/13.
// Copyright © 2013 Damien Bendejacq. All rights reserved.
//

#ifndef __VECTOR2D_H__
#define __VECTOR2D_H__

#include <cstdlib>
#include <cmath>

namespace Jackbengine {

template<typename T>
struct Vector2d
{
    Vector2d()
        : Vector2d(0, 0)
    { }

    Vector2d(T x, T y)
        : x(x),
          y(y)
    { }

    ~Vector2d() = default;

    void absolute()
    {
        x = fabs(x);
        y = fabs(y);
    }
    void absoluteX()
    {
        x = fabs(x);
    }
    void absoluteY()
    {
        y = fabs(y);
    }

    float getLength() const
    {
        return sqrt(x * x + y * y);
    }

    void invert()
    {
        x = -x;
        y = -y;
    }
    void invertX()
    {
        x = -x;
    }
    void invertY()
    {
        y = -y;
    }

    bool isZero() const
    {
        return 0.0f == x && 0.0f == y;
    }

    void negate()
    {
        x = fabs(x) * -1.0f;
        y = fabs(y) * -1.0f;
    }
    void negateX()
    {
        x = fabs(x) * -1.0f;
    }
    void negateY()
    {
        y = fabs(y) * -1.0f;
    }

    void normalize()
    {
        if (isZero())
        {
            return;
        }

        float n = x * x + y * y;

        if (1.0f == n)
        {
            return;
        }

        n = sqrt(n);
        n = 1.0f / n;

        x *= n;
        y *= n;
    }

    T x;
    T y;
    /*union
    {
        struct
        {
            T x;
            T y;
        };
        struct
        {
            T val[2];
        };
    };*/
};

using Vec2f = Vector2d<float>;
using Vec2i = Vector2d<int>;

} // namespace Jackbengine

#endif // __VECTOR2D_H__
