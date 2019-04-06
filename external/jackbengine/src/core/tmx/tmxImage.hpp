//
// tmxImage.hpp
// jackbengine
//
// Created by Damien Bendejacq on 28/10/14.
// Copyright © 2014 Damien Bendejacq. All rights reserved.
//

#ifndef __TMX_IMAGE_H__
#define __TMX_IMAGE_H__

#include "common.hpp"
#include "tinyxml/tinyxml.h"

namespace Jackbengine {

class TmxImage
{
    DISALLOW_COPY_AND_MOVE(TmxImage)

    friend class TmxTileset;

public:
    const char* source() const;
    int width() const;
    int height() const;

private:
    TmxImage() = default;

    void load(const TiXmlElement *element);

    const char *m_source {nullptr};
    int m_width {0};
    int m_height {0};
};

} // namespace Jackbengine

#endif // __TMX_IMAGE_H__
