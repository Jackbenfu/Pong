//
// tmxMap.cpp
// jackbengine
//
// Created by Damien Bendejacq on 26/10/14.
// Copyright © 2014 Damien Bendejacq. All rights reserved.
//

#include "tmxMap.hpp"
#include "platform.hpp"

using namespace Jackbengine;

TmxMap::TmxMap()
    : m_doc {std::make_unique<TiXmlDocument>()},
      m_tileset {std::unique_ptr<TmxTileset>(new TmxTileset())},
      tmxProperties {std::unique_ptr<TmxPropertyGroup>(new TmxPropertyGroup())}
{ }

void TmxMap::loadFromFile(const char *file)
{
    char filePath[255];

#ifdef __APPLE__

    // BEGIN extract
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFStringRef resourceString = CFStringCreateWithCString(nullptr, file, kCFStringEncodingASCII);
    CFURLRef resourceUrl = CFBundleCopyResourceURL(mainBundle, resourceString, nullptr, nullptr);
    CFURLGetFileSystemRepresentation(resourceUrl, true, (UInt8*)filePath, 4096);
    CFRelease(resourceUrl);
    CFRelease(resourceString);
    CFBundleUnloadExecutable(mainBundle);
    // END extract

#else

    strcpy(filePath, file);

#endif

    if (!m_doc->LoadFile(filePath))
    {
        throw std::runtime_error(m_doc->ErrorDesc());
    }

    loadContents();
}

void TmxMap::loadFromMemory(const unsigned char *data)
{
    if (nullptr == m_doc->Parse((char*)data))
    {
        throw std::runtime_error(m_doc->ErrorDesc());
    }

    loadContents();
}

int TmxMap::width() const
{
    return m_width;
}

int TmxMap::height() const
{
    return m_height;
}

int TmxMap::tileWidth() const
{
    return m_tileWidth;
}

int TmxMap::tileHeight() const
{
    return m_tileHeight;
}

const TmxTileset* TmxMap::tileset() const
{
    return m_tileset.get();
}

const TmxLayer* TmxMap::layer(int index) const
{
    if (m_layers.size() > (size_t)index)
    {
        return m_layers[index].get();
    }

    return nullptr;
}

const TmxLayer* TmxMap::layer(const char *name) const
{
    for (auto& layer : m_layers)
    {
        if (0 == strcmp(name, layer->name()))
        {
            return layer.get();
        }
    }

    return nullptr;
}

int TmxMap::layerCount() const
{
    return (int)m_layers.size();
}

const TmxObjectGroup* TmxMap::objectGroup(int index) const
{
    if (m_objectGroups.size() > (size_t)index)
    {
        return m_objectGroups[index].get();
    }

    return nullptr;
}

const TmxObjectGroup* TmxMap::objectGroup(const char *name) const
{
    for (auto& objectGroup : m_objectGroups)
    {
        if (0 == strcmp(name, objectGroup->name()))
        {
            return objectGroup.get();
        }
    }

    return nullptr;
}

int TmxMap::objectGroupCount() const
{
    return (int)m_objectGroups.size();
}

const TmxPropertyGroup* TmxMap::properties() const
{
    return tmxProperties.get();
}

void TmxMap::loadContents()
{
    const TiXmlNode *node = m_doc->FirstChild("map");
    const TiXmlElement *map = node->ToElement();

    map->Attribute("width", &m_width);
    map->Attribute("height", &m_height);
    map->Attribute("tilewidth", &m_tileWidth);
    map->Attribute("tileheight", &m_tileHeight);

    node = map->FirstChild();
    while (nullptr != node)
    {
        if (0 == strcmp("tileset", node->Value()))
        {
            m_tileset->load(node->ToElement());
        }
        else if (0 == strcmp("layer", node->Value()))
        {
            auto layer = std::unique_ptr<TmxLayer>(new TmxLayer());
            layer->load(node->ToElement());
            m_layers.push_back(std::move(layer));
        }
        else if (0 == strcmp("objectgroup", node->Value()))
        {
            auto objectGroup = std::unique_ptr<TmxObjectGroup>(new TmxObjectGroup());
            objectGroup->load(node->ToElement());
            m_objectGroups.push_back(std::move(objectGroup));
        }
        else if (0 == strcmp("properties", node->Value()))
        {
            tmxProperties->load(node->ToElement());
        }

        node = node->NextSibling();
    }
}
