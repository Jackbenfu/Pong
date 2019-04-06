//
// rect.hpp
// jackbengine
//
// Created by Damien Bendejacq on 26/06/15.
// Copyright © 2015 Damien Bendejacq. All rights reserved.
//

#ifndef __RECT_H__
#define __RECT_H__

namespace Jackbengine {

template<typename T>
struct Rect
{
    Rect()
        : Rect(0, 0, 0, 0)
    { }

    Rect(T x, T y, T w, T h)
        : x(x),
          y(y),
          w(w),
          h(h)
    { }

    ~Rect() = default;

    T x;
    T y;
    T w;
    T h;
};

using Recti = Rect<int>;
using Rectf = Rect<float>;

} // namespace Jackbengine

#endif // __RECT_H__
