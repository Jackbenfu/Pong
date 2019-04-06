//
// nameComponent.hpp
// jackbengine
//
// Created by Damien Bendejacq on 29/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __NAME_COMPONENT_H__
#define __NAME_COMPONENT_H__

#include "component/generic/stringComponent.hpp"

namespace Jackbengine {

class NameComponent : public Component
{
    DISALLOW_COPY_AND_MOVE(NameComponent)

public:
    explicit NameComponent(const std::string& name);
    ~NameComponent() override = default;

    const std::string& get() const;
    void set(const std::string& name);

private:
    StringComponent m_value;
};

using Name = NameComponent;

} // namespace Jackbengine

#endif // __NAME_COMPONENT_H__
