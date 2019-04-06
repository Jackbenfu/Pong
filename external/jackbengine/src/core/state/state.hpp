//
// state.hpp
// jackbengine
//
// Created by Damien Bendejacq on 26/09/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __STATE_H__
#define __STATE_H__

#include "common.hpp"

namespace Jackbengine {

class StateMachine;

class State
{
    DISALLOW_COPY_AND_MOVE(State)

public:
    State() = delete;
    explicit State(StateMachine& stateMachine)
        : m_stateMachine {stateMachine}
    { }

    virtual ~State() = default;

    virtual void enter() { }
    virtual void frame(float) { }
    virtual void exit() { }

protected:
    StateMachine& stateMachine() const { return m_stateMachine; }

private:
    StateMachine& m_stateMachine;
};

} // namespace Jackbengine

#endif // __STATE_H__
