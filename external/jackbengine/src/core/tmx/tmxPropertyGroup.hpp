//
// tmxPropertyGroup.hpp
// jackbengine
//
// Created by Damien Bendejacq on 17/11/14.
// Copyright © 2014 Damien Bendejacq. All rights reserved.
//

#ifndef __TMX_PROPERTYGROUP_H__
#define __TMX_PROPERTYGROUP_H__

#include <vector>
#include <memory>
#include "common.hpp"
#include "tinyxml/tinyxml.h"
#include "tmxProperty.hpp"

namespace Jackbengine {

class TmxPropertyGroup
{
    DISALLOW_COPY_AND_MOVE(TmxPropertyGroup)

    friend class TmxMap;
    friend class TmxTileset;
    friend class TmxObjectGroup;
    friend class TmxObject;
    friend class TmxLayer;

public:
    bool hasProperty(const char *name) const;

    const char* property(const char *name) const;
    bool intProperty(const char *name, int *value) const;
    bool unsignedIntProperty(const char *name, uint *value) const;
    bool boolProperty(const char *name, bool *value) const;
    bool doubleProperty(const char *name, double *value) const;

private:
    TmxPropertyGroup() = default;

    void load(const TiXmlElement *element);
    const TmxProperty *rawProperty(const char *name) const;

    std::vector<std::unique_ptr<TmxProperty>> m_properties;
};

} // namespace Jackbengine

#endif // __TMX_PROPERTYGROUP_H__
