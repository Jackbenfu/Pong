//
// componentCollection.hpp
// jackbengine
//
// Created by Damien Bendejacq on 20/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __COMPONENT_COLLECTION_H__
#define __COMPONENT_COLLECTION_H__

#include "component/component.hpp"
#include "core/collection/heterogeneousCollection.hpp"

namespace Jackbengine {

class ComponentCollection
{
    DISALLOW_COPY_AND_MOVE(ComponentCollection)

public:
    ComponentCollection() = default;
    ~ComponentCollection() = default;

    template<typename TComponent, typename ...Args>
    void add(Args&& ...args);

    template<typename TComponent>
    TComponent& get() const;

    template<typename TComponent>
    bool any() const;

    template<typename TComponent>
    void remove();

    template<typename TComponent>
    void enable(bool enable);

private:
    HeterogeneousCollection<Component> m_components;
};

template<typename TComponent, typename ...Args>
void ComponentCollection::add(Args&& ...args)
{
    m_components.add<TComponent>(std::forward<Args>(args)...);
}

template<typename TComponent>
TComponent& ComponentCollection::get() const
{
    return m_components.get<TComponent>();
}

template<typename TComponent>
bool ComponentCollection::any() const
{
    return m_components.any<TComponent>();
}

template<typename TComponent>
void ComponentCollection::remove()
{
    m_components.remove<TComponent>();
}

template<typename TComponent>
void ComponentCollection::enable(bool enable)
{
    m_components.enable<TComponent>(enable);
}

} // namespace Jackbengine

#endif // __COMPONENT_COLLECTION_H__
