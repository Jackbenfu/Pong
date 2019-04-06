//
// profile.hpp
// jackbengine
//
// Created by Damien Bendejacq on 02/07/15.
// Copyright © 2015 Damien Bendejacq. All rights reserved.
//

#ifndef __PROFILE_H__
#define __PROFILE_H__

#include <chrono>
#include <iostream>

namespace Jackbengine {

#define PROFILE_SECONDS(name)       Profile<std::chrono::seconds> __profile__(name)
#define PROFILE_MILLISECONDS(name)  Profile<std::chrono::milliseconds> __profile__(name)
#define PROFILE_MICROSECONDS(name)  Profile<std::chrono::microseconds> __profile__(name)
#define PROFILE_NANOSECONDS(name)   Profile<std::chrono::nanoseconds> __profile__(name)

template<typename Precision>
class Profile
{
    using clock = std::chrono::high_resolution_clock;

public:
    explicit Profile(const char *name)
        : m_name {name},
          m_start {clock::now()}
    { }

    ~Profile()
    {
        auto duration = clock::now() - m_start;

        std::cout
            << "Time taken for scope " << m_name << ": "
            << std::chrono::duration_cast<Precision>(duration).count() << " " << unit()
            << std::endl;
    }

private:
    inline const char* unit();

    const char *m_name;
    clock::time_point m_start;
};

template<>
inline const char* Profile<std::chrono::seconds>::unit()
{
    return "seconds";
}

template<>
inline const char* Profile<std::chrono::milliseconds>::unit()
{
    return "milliseconds";
}

template<>
inline const char* Profile<std::chrono::microseconds>::unit()
{
    return "microseconds";
}

template<>
inline const char* Profile<std::chrono::nanoseconds>::unit()
{
    return "nanoseconds";
}

} // namespace Jackbengine

#endif // __PROFILE_H__
