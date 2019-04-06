//
// tmxTileset.cpp
// jackbengine
//
// Created by Damien Bendejacq on 26/10/14.
// Copyright © 2014 Damien Bendejacq. All rights reserved.
//

#include "tmxTileset.hpp"

using namespace Jackbengine;

TmxTileset::TmxTileset()
    : m_image {std::unique_ptr<TmxImage>(new TmxImage())},
      m_properties {std::unique_ptr<TmxPropertyGroup>(new TmxPropertyGroup())}
{ }

const char* TmxTileset::name() const
{
    return m_name;
}

int TmxTileset::firstGid() const
{
    return m_firstGid;
}

int TmxTileset::tileWidth() const
{
    return m_tileWidth;
}

int TmxTileset::tileHeight() const
{
    return m_tileHeight;
}

const TmxImage* TmxTileset::image() const
{
    return m_image.get();
}

const TmxPropertyGroup* TmxTileset::properties() const
{
    return m_properties.get();
}

void TmxTileset::load(const TiXmlElement *element)
{
    m_name = element->Attribute("name");
    element->Attribute("firstgid", &m_firstGid);
    element->Attribute("tilewidth", &m_tileWidth);
    element->Attribute("tileheight", &m_tileHeight);

    auto node = element->FirstChild();
    while (nullptr != node)
    {
        if (0 == strcmp("image", node->Value()))
        {
            m_image->load(node->ToElement());
        }
        else if (0 == strcmp("properties", node->Value()))
        {
            m_properties->load(node->ToElement());
        }

        node = node->NextSibling();
    }
}
