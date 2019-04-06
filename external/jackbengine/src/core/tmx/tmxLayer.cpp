//
// tmxLayer.cpp
// jackbengine
//
// Created by Damien Bendejacq on 28/10/14.
// Copyright © 2014 Damien Bendejacq. All rights reserved.
//

#include "tmxLayer.hpp"

using namespace Jackbengine;

TmxLayer::TmxLayer() = default;

const char* TmxLayer::name() const
{
    return m_name;
}

int TmxLayer::width() const
{
    return m_width;
}

int TmxLayer::height() const
{
    return m_height;
}

int TmxLayer::tileId(int x, int y) const
{
    auto pos = y * m_width + x;
    if (m_width * m_height > pos)
    {
        return m_data[pos];
    }

    return -1;
}

const TmxPropertyGroup* TmxLayer::properties() const
{
    return m_properties.get();
}

void TmxLayer::load(const TiXmlElement *element)
{
    m_name = element->Attribute("name");
    element->Attribute("width", &m_width);
    element->Attribute("height", &m_height);

    auto node = element->FirstChild();
    while (nullptr != node)
    {
        if (0 == strcmp("data", node->Value()))
        {
            auto data = element->FirstChildElement("data");
            auto encoding = data->Attribute("encoding");

            if (0 == strcmp("csv", encoding))
            {
                auto delimiters = ",";

                auto csv = strdup(data->GetText());
                auto token = strtok(csv, delimiters);

                m_data.reserve((size_t)m_width * (size_t)m_height);
                auto i = 0;

                while (nullptr != token)
                {
                    int tileId;
                    char *end;
                    tileId = (int)strtol(token, &end, 10);

                    m_data[i++] = tileId;
                    
                    token = strtok(nullptr, delimiters);
                }

                free(csv);
            }
        }
        else if (0 == strcmp("properties", node->Value()))
        {
            m_properties = std::unique_ptr<TmxPropertyGroup>(new TmxPropertyGroup());
            m_properties->load(node->ToElement());
        }

        node = node->NextSibling();
    }
}
