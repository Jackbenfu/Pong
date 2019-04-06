//
// tmxObjectGroup.hpp
// jackbengine
//
// Created by Damien Bendejacq on 29/10/14.
// Copyright © 2014 Damien Bendejacq. All rights reserved.
//

#ifndef __TMX_OBJECTGROUP_H__
#define __TMX_OBJECTGROUP_H__

#include <vector>
#include "tinyxml/tinyxml.h"
#include "tmxObject.hpp"
#include "tmxPropertyGroup.hpp"

namespace Jackbengine {

class TmxObjectGroup
{
    DISALLOW_COPY_AND_MOVE(TmxObjectGroup)

    friend class TmxMap;

public:
    const char* name() const;

    const TmxObject* object(int index) const;
    const TmxObject* object(const char *name) const;
    int objectCount() const;

    int originX() const;
    int originY() const;

    bool hasProperty(const char *name) const;
    const TmxPropertyGroup* properties() const;

private:
    TmxObjectGroup();

    void load(const TiXmlElement *element);

    const char* m_name {nullptr};
    std::vector<std::unique_ptr<TmxObject>> m_objects;
    std::unique_ptr<TmxPropertyGroup> m_properties;
};

} // namespace Jackbengine

#endif // __TMX_OBJECTGROUP_H__
