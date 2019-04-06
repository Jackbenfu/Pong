//
// tmxProperty.hpp
// jackbengine
//
// Created by Damien Bendejacq on 17/11/14.
// Copyright © 2014 Damien Bendejacq. All rights reserved.
//

#ifndef __TMX_PROPERTY_H__
#define __TMX_PROPERTY_H__

#include <string>
#include "common.hpp"
#include "tinyxml/tinyxml.h"

namespace Jackbengine {

class TmxProperty
{
    DISALLOW_COPY_AND_MOVE(TmxProperty)

    friend class TmxPropertyGroup;

public:
    const char* name() const;
    const char* value() const;

    bool intValue(int *value) const;
    bool unsignedIntValue(uint *value) const;
    bool boolValue(bool *value) const;
    bool doubleValue(double *value) const;

private:
    TmxProperty() = default;

    void load(const TiXmlElement *element);

    const TiXmlElement *m_element {nullptr};
    const char *m_name {nullptr};
    const char *m_value {nullptr};
};

} // namespace Jackbengine

#endif // __TMX_PROPERTY_H__
