//
// tmxLayer.hpp
// jackbengine
//
// Created by Damien Bendejacq on 28/10/14.
// Copyright © 2014 Damien Bendejacq. All rights reserved.
//

#ifndef __TMX_LAYER_H__
#define __TMX_LAYER_H__

#include <vector>
#include "tinyxml/tinyxml.h"
#include "tmxPropertyGroup.hpp"

namespace Jackbengine {

class TmxLayer
{
    DISALLOW_COPY_AND_MOVE(TmxLayer)

    friend class TmxMap;

public:
    ~TmxLayer() = default;

    const char* name() const;
    int width() const;
    int height() const;

    int tileId(int x, int y) const;

    const TmxPropertyGroup* properties() const;

private:
    TmxLayer();

    void load(const TiXmlElement *element);

    const char *m_name {nullptr};
    int m_width {0};
    int m_height {0};
    //int *m_data {nullptr};
    std::vector<int> m_data;

    std::unique_ptr<TmxPropertyGroup> m_properties;
};

} // namespace Jackbengine

#endif // __TMX_LAYER_H__
