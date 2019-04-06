//
// stringComponent.hpp
// jackbengine
//
// Created by Damien Bendejacq on 31/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __STRING_COMPONENT_H__
#define __STRING_COMPONENT_H__

#include <string>
#include "component/component.hpp"

namespace Jackbengine {

class StringComponent : public Component
{
    DISALLOW_COPY_AND_MOVE(StringComponent)

public:
    explicit StringComponent(const std::string& value);
    ~StringComponent() override = default;

    const std::string& get() const;
    void set(const std::string& value);

private:
    std::string m_value;
};

using String = StringComponent;

} // namespace Jackbengine

#endif // __STRING_COMPONENT_H__
