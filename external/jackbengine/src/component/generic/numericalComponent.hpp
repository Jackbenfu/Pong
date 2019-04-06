//
// numericalComponent.hpp
// jackbengine
//
// Created by Damien Bendejacq on 29/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __NUMERICAL_COMPONENT_H__
#define __NUMERICAL_COMPONENT_H__

#include "component/component.hpp"

namespace Jackbengine {

template<typename T>
class NumericalComponent : public Component
{
    static_assert(std::is_arithmetic<T>::value);

    DISALLOW_COPY_AND_MOVE(NumericalComponent)

public:
    NumericalComponent(T value);
    ~NumericalComponent() override = default;

    T get() const;
    void set(T value);

    void increment(T by);
    void decrement(T by);

private:
    T m_value;
};

template<typename T>
using Numerical = NumericalComponent<T>;

template <typename T>
NumericalComponent<T>::NumericalComponent(T value)
    : m_value {value}
{ }

template <typename T>
T NumericalComponent<T>::get() const
{
    return m_value;
}

template <typename T>
void NumericalComponent<T>::set(T value)
{
    m_value = value;
}

template <typename T>
void NumericalComponent<T>::increment(T by)
{
    m_value += by;
}

template <typename T>
void NumericalComponent<T>::decrement(T by)
{
    m_value -= by;
}

} // namespace Jackbengine

#endif // __NUMERICAL_COMPONENT_H__
