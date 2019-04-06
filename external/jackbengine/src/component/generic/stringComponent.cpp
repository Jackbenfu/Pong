//
// stringComponent.cpp
// jackbengine
//
// Created by Damien Bendejacq on 31/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "stringComponent.hpp"

using namespace Jackbengine;

StringComponent::StringComponent(const std::string& value)
    : m_value {value}
{ }

const std::string& StringComponent::get() const
{
    return m_value;
}

void StringComponent::set(const std::string& value)
{
    m_value = value;
}
