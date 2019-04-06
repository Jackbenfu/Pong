//
// tmxObject.hpp
// jackbengine
//
// Created by Damien Bendejacq on 29/10/14.
// Copyright © 2014 Damien Bendejacq. All rights reserved.
//

#ifndef __TMX_OBJECT_H__
#define __TMX_OBJECT_H__

#include "tinyxml/tinyxml.h"
#include "tmxPropertyGroup.hpp"
#include "tmxText.hpp"

namespace Jackbengine {

class TmxObject
{
    DISALLOW_COPY_AND_MOVE(TmxObject)

    friend class TmxObjectGroup;

public:
    const char* name() const;
    int gid() const;
    bool hasGid() const;
    int x() const;
    int y() const;
    int width() const;
    int height() const;

    const char* type() const;

    bool hasProperty(const char *name) const;
    const TmxPropertyGroup* properties() const;

    bool hasText() const;
    const TmxText* text() const;

private:
    TmxObject() = default;

    void load(const TiXmlElement *element);

    const char* m_name {nullptr};
    const char *m_type {nullptr};
    int m_gid {0};
    int m_x {0};
    int m_y {0};
    int m_width {0};
    int m_height {0};

    std::unique_ptr<TmxPropertyGroup> m_properties;
    std::unique_ptr<TmxText> m_text;
};

} // namespace Jackbengine

#endif // __TMX_OBJECT_H__
