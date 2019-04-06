//
// tmxTileset.hpp
// jackbengine
//
// Created by Damien Bendejacq on 26/10/14.
// Copyright © 2014 Damien Bendejacq. All rights reserved.
//

#ifndef __TMX_TILESET_H__
#define __TMX_TILESET_H__

#include "tinyxml/tinyxml.h"
#include "tmxImage.hpp"
#include "tmxPropertyGroup.hpp"

namespace Jackbengine {

class TmxTileset
{
    DISALLOW_COPY_AND_MOVE(TmxTileset)

    friend class TmxMap;

public:
    const char* name() const;
    int firstGid() const;
    int tileWidth() const;
    int tileHeight() const;

    const TmxImage* image() const;

    const TmxPropertyGroup* properties() const;

private:
    TmxTileset();

    void load(const TiXmlElement *element);

    const char *m_name {nullptr};
    int m_firstGid {1};
    int m_tileWidth {0};
    int m_tileHeight {0};

    std::unique_ptr<TmxImage> m_image;
    std::unique_ptr<TmxPropertyGroup> m_properties;
};

} // namespace Jackbengine

#endif // __TMX_TILESET_H__
