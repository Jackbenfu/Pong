//
// zOrderComponent.hpp
// jackbengine
//
// Created by Damien Bendejacq on 29/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __Z_ORDER_COMPONENT_H__
#define __Z_ORDER_COMPONENT_H__

#include "component/component.hpp"

namespace Jackbengine {

class ZOrderComponent : public Component
{
    DISALLOW_COPY_AND_MOVE(ZOrderComponent)

public:
    ZOrderComponent() = default;
    explicit ZOrderComponent(int index);

    ~ZOrderComponent() override = default;

    int index() const;
    void setIndex(int index);

private:
    int m_index {0};
};

using ZOrder = ZOrderComponent;

} // namespace Jackbengine

#endif // __Z_ORDER_COMPONENT_H__
