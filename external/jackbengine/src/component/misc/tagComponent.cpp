//
// tagComponent.cpp
// jackbengine
//
// Created by Damien Bendejacq on 29/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "tagComponent.hpp"

using namespace Jackbengine;

TagComponent::TagComponent(const std::string& tag)
    : m_value(tag)
{ }

const std::string& TagComponent::get() const
{
    return m_value.get();
}

void TagComponent::set(const std::string& tag)
{
    m_value.set(tag);
}
