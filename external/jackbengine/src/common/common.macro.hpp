//
// common.macro.hpp
// jackbengine
//
// Created by Damien Bendejacq on 29/06/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __COMMON_MACRO_H__
#define __COMMON_MACRO_H__

namespace Jackbengine {

#define DISALLOW_COPY_AND_MOVE(T)           \
    public:                                 \
        T(const T&) = delete;               \
        void operator=(const T&) = delete;  \
        T(T&&) = delete;                    \
        void operator=(T&&) = delete;

#define GET_TYPE_ID(T)      typeid(T).hash_code()
#define GET_TYPE_NAME(T)    typeid(T).name()

} // namespace Jackbengine

#endif // __COMMON_MACRO_H__
