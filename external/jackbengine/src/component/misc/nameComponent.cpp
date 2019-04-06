//
// nameComponent.cpp
// jackbengine
//
// Created by Damien Bendejacq on 29/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "nameComponent.hpp"

using namespace Jackbengine;

NameComponent::NameComponent(const std::string& name)
    : m_value {name}
{ }

const std::string& NameComponent::get() const
{
    return m_value.get();
}

void NameComponent::set(const std::string& name)
{
    m_value.set(name);
}
