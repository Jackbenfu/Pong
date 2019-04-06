//
// zOrderComponent.cpp
// jackbengine
//
// Created by Damien Bendejacq on 29/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "zOrderComponent.hpp"

using namespace Jackbengine;

ZOrderComponent::ZOrderComponent(int index)
    : m_index {index}
{ }

int ZOrderComponent::index() const
{
    return m_index;
}

void ZOrderComponent::setIndex(int index)
{
    m_index = index;
}
