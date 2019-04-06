//
// tmxText.hpp
// jackbengine
//
// Created by Damien Bendejacq on 04/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __TMX_TEXT_H__
#define __TMX_TEXT_H__

#include "common.hpp"
#include "tinyxml/tinyxml.h"

namespace Jackbengine {

class TmxText
{
    DISALLOW_COPY_AND_MOVE(TmxText)

    friend class TmxObject;

public:
    int pixelsize() const;
    const char *color() const;
    const char *halign() const;
    const char *valign() const;
    const char *text() const;

private:
    TmxText() = default;

    void load(const TiXmlElement *element);

    int m_pixelsize {0};
    const char *m_color {nullptr};
    const char *m_halign {nullptr};
    const char *m_valign {nullptr};
    const char *m_text {nullptr};
};

} // namespace Jackbengine

#endif // __TMX_TEXT_H__
