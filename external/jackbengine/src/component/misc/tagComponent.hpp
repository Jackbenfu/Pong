//
// tagComponent.hpp
// jackbengine
//
// Created by Damien Bendejacq on 29/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __TAG_COMPONENT_H__
#define __TAG_COMPONENT_H__

#include "component/generic/stringComponent.hpp"

namespace Jackbengine {

class TagComponent : public Component
{
    DISALLOW_COPY_AND_MOVE(TagComponent)

public:
    explicit TagComponent(const std::string& tag);
    ~TagComponent() override = default;

    const std::string& get() const;
    void set(const std::string& tag);

private:
    StringComponent m_value;
};

using Tag = TagComponent;

} // namespace Jackbengine

#endif // __TAG_COMPONENT_H__
