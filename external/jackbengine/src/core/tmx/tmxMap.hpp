//
// tmxMap.hpp
// jackbengine
//
// Created by Damien Bendejacq on 26/10/14.
// Copyright © 2014 Damien Bendejacq. All rights reserved.
//

#ifndef __TMX_MAP_H__
#define __TMX_MAP_H__

#include <vector>

#include "tinyxml/tinyxml.h"
#include "tmxTileset.hpp"
#include "tmxLayer.hpp"
#include "tmxObjectGroup.hpp"
#include "tmxPropertyGroup.hpp"

namespace Jackbengine {

class TmxMap
{
    DISALLOW_COPY_AND_MOVE(TmxMap)

public:
    TmxMap();

    void loadFromFile(const char *file);
    void loadFromMemory(const unsigned char *data);

    int width() const;
    int height() const;
    int tileWidth() const;
    int tileHeight() const;

    const TmxTileset* tileset() const;

    const TmxLayer* layer(int index) const;
    const TmxLayer* layer(const char *name) const;
    int layerCount() const;

    const TmxObjectGroup* objectGroup(int index) const;
    const TmxObjectGroup* objectGroup(const char *name) const;
    int objectGroupCount() const;

    const TmxPropertyGroup* properties() const;

private:
    void loadContents();

    int m_width {0};
    int m_height {0};
    int m_tileWidth {0};
    int m_tileHeight {0};

    std::unique_ptr<TiXmlDocument> m_doc;
    std::unique_ptr<TmxTileset> m_tileset;
    std::vector<std::unique_ptr<TmxLayer>> m_layers;
    std::vector<std::unique_ptr<TmxObjectGroup>> m_objectGroups;
    std::unique_ptr<TmxPropertyGroup> tmxProperties;
};

} // namespace Jackbengine

#endif // __TMX_MAP_H__
