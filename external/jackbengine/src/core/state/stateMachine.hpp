//
// stateMachine.hpp
// jackbengine
//
// Created by Damien Bendejacq on 26/09/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

#include <string>
#include <unordered_map>
#include <memory>
#include "state.hpp"

namespace Jackbengine {

class StateMachine
{
    DISALLOW_COPY_AND_MOVE(StateMachine)

public:
    StateMachine() = default;
    ~StateMachine();

    void start();
    void frame(float delta);

    template<typename TState, typename ...Args>
    void addState(Args&& ...args);

    template<typename TState>
    void goToState();

private:
    size_t m_firstStateTypeId {0};
    State *m_currentState {nullptr};

    std::unordered_map<size_t, std::unique_ptr<State>> m_states;
};

template<typename TState, typename ...Args>
void StateMachine::addState(Args&& ...args)
{
    static_assert(std::is_base_of<State, TState>::value);

    const auto typeId = GET_TYPE_ID(TState);
    if (m_states.find(typeId) != m_states.end())
    {
        throw std::runtime_error("State already exists: " + std::string(GET_TYPE_NAME(TState)));
    }

    m_states[typeId] = std::make_unique<TState>(*this, std::forward<Args>(args)...);

    if (1 == m_states.size())
    {
        m_firstStateTypeId = typeId;
    }
}

template<typename TState>
void StateMachine::goToState()
{
    static_assert(std::is_base_of<State, TState>::value);

    const auto typeId = GET_TYPE_ID(TState);
    const auto it = m_states.find(typeId);
    if (it == m_states.end())
    {
        throw std::runtime_error("State does not exist: " + std::string(GET_TYPE_NAME(TState)));
    }

    m_currentState->exit();
    m_currentState = it->second.get();
    m_currentState->enter();
}

} // namespace Jackbengine

#endif // __STATE_MACHINE_H__
