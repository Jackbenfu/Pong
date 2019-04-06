//
// stateMachine.cpp
// jackbengine
//
// Created by Damien Bendejacq on 26/09/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "stateMachine.hpp"

using namespace Jackbengine;

StateMachine::~StateMachine()
{
    if (nullptr != m_currentState)
    {
        m_currentState->exit();
    }
}

void StateMachine::start()
{
    if (m_states.empty())
    {
        throw std::runtime_error("No state defined");
    }

    m_currentState = m_states[m_firstStateTypeId].get();
    m_currentState->enter();
}

void StateMachine::frame(float delta)
{
    m_currentState->frame(delta);
}
