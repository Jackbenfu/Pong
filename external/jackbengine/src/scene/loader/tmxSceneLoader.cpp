//
// tmxSceneLoader.cpp
// jackbengine
//
// Created by Damien Bendejacq on 04/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "tmxSceneLoader.hpp"
#include "component/body/transformComponent.hpp"
#include "component/body/shape/boxShapeComponent.hpp"
#include "component/layout/containerComponent.hpp"
#include "component/view/spriteComponent.hpp"
#include "system/animation/motionSystem.hpp"
#include "system/input/mouseEventTriggerSystem.hpp"
#include "system/physic/aabbCollisionSystem.hpp"
#include "system/render/textRenderSystem.hpp"
#include "system/render/spriteRenderSystem.hpp"

using namespace Jackbengine;

TmxSceneLoader::TmxSceneLoader(
    Scene& scene, const unsigned char *tmxData,
    const void *tilesetData, size_t tilesetDataSize,
    const void *fontData, size_t fontDataSize
)
    : m_scene {scene},
      m_tilesetData {tilesetData},
      m_tilesetDataSize {tilesetDataSize},
      m_fontData {fontData},
      m_fontDataSize {fontDataSize}
{
    m_map.loadFromMemory(tmxData);
    loadContents();
}

Entity TmxSceneLoader::entity(const char *name) const
{
    const auto it = m_entities.find(name);
    if (it == m_entities.end())
    {
        throw std::runtime_error(std::string("Entity does not exist: ") + name);
    }

    return it->second;
}

void TmxSceneLoader::loadContents()
{
    loadSystems();

    for (auto i = 0; i < m_map.layerCount(); ++i)
    {
        loadLayer(i);
    }

    for (auto i = 0; i < m_map.objectGroupCount(); ++i)
    {
        loadObjectGroup(i);
    }
}

void TmxSceneLoader::loadSystems()
{
    m_scene.addSystem<MotionSystem>();
    m_scene.addSystem<MouseEventTriggerSystem>(m_scene.input());
    m_scene.addSystem<AABBCollisionSystem>();
    m_scene.addSystem<SpriteRenderSystem>(m_scene.renderer());
    m_scene.addSystem<TextRenderSystem>(m_scene.renderer());
}

void TmxSceneLoader::loadLayer(int index)
{
    auto layer = m_map.layer(index);

    auto entity = m_scene.addEntity();
    m_scene.addComponent<Transform>(entity);
    m_scene.addComponent<Sprite>(
        entity, m_scene.renderer(), m_map, *layer, m_tilesetData, m_tilesetDataSize
    );

    m_entities.emplace(layer->name(), entity);
}

void TmxSceneLoader::loadObjectGroup(int index)
{
    auto objectGroup = m_map.objectGroup(index);

    bool isEntity {false};
    objectGroup->properties()->boolProperty("isEntity", &isEntity);
    if (isEntity)
    {
        loadEntityFromObjectGroup(objectGroup);
    }
    else
    {
        for (auto i = 0; i < objectGroup->objectCount(); ++i)
        {
            loadEntityFromObject(objectGroup->object(i));
        }
    }
}

void TmxSceneLoader::loadEntityFromObjectGroup(const TmxObjectGroup *objectGroup)
{
    const TmxObject *shape {nullptr};
    for (auto i = 0; i < objectGroup->objectCount(); ++i)
    {
        auto object = objectGroup->object(i);
        auto type = object->type();
        if (nullptr != type && 0 == strcmp("shape", type))
        {
            shape = object;
            break;
        }
    }

    if (nullptr == shape)
    {
        throw std::runtime_error(
            std::string("Entity loaded from object group must have a child object of type shape (") +
            objectGroup->name() + ")"
        );
    }

    auto entity = m_scene.addEntity();
    m_scene.addComponent<Transform>(entity, shape->x(), shape->y());
    m_scene.addComponent<BoxShape>(entity, shape->width(), shape->height());

    if (hasObjectGroupChildGid(objectGroup))
    {
        m_scene.addComponent<Sprite>(
            entity, m_scene.renderer(), m_map, *objectGroup, m_tilesetData, m_tilesetDataSize
        );
    }

    m_entities.emplace(objectGroup->name(), entity);
}

void TmxSceneLoader::loadEntityFromObject(const TmxObject *object)
{
    auto entity = m_scene.addEntity();
    m_scene.addComponent<Transform>(entity, object->x(), object->y());
    m_scene.addComponent<BoxShape>(entity, object->width(), object->height());

    if (object->hasText())
    {
        loadTextFromObject(object, entity);
    }

    m_entities.emplace(object->name(), entity);
}

void TmxSceneLoader::loadTextFromObject(const TmxObject *object, Entity entity)
{
    auto text = object->text();
    auto pixelSize = text->pixelsize();
    auto layout = getTextLayout(text);
    auto color = getTextColor(text);

    m_scene.addComponent<Container>(entity, object->x(), object->y(), object->width(), object->height());

    m_scene.addComponent<Text>(
        entity, m_scene.renderer(), text->text(), layout, color, pixelSize, m_fontData, m_fontDataSize
    );
}

bool TmxSceneLoader::hasObjectGroupChildGid(const TmxObjectGroup *objectGroup) const
{
    for (auto i = 0; i < objectGroup->objectCount(); ++i)
    {
        if (objectGroup->object(i)->hasGid())
        {
            return true;
        }
    }

    return false;
}

TextLayout TmxSceneLoader::getTextLayout(const TmxText *text) const
{
    const auto isLeft = [](const char *halign) { return nullptr == halign || 0 == strcmp("left", halign); };
    const auto isRight = [](const char *halign) { return 0 == strcmp("right", halign); };
    const auto isCenter = [](const char *align) { return 0 == strcmp("center", align); };
    const auto isTop = [](const char *valign) { return nullptr == valign || 0 == strcmp("top", valign); };
    const auto isBottom = [](const char *valign) { return 0 == strcmp("bottom", valign); };

    auto halign = text->halign();
    auto valign = text->valign();

    auto layout = TextLayout::LeftTop;
    if (isLeft(halign) && isTop(valign))
    {
        layout = TextLayout::LeftTop;
    }
    else if (isLeft(halign) && isCenter(valign))
    {
        layout = TextLayout::LeftCenter;
    }
    else if (isLeft(halign) && isBottom(valign))
    {
        layout = TextLayout::LeftBottom;
    }
    else if (isCenter(halign) && isTop(valign))
    {
        layout = TextLayout::CenterTop;
    }
    else if (isCenter(halign) && isCenter(valign))
    {
        layout = TextLayout::CenterCenter;
    }
    else if (isCenter(halign) && isBottom(valign))
    {
        layout = TextLayout::CenterBottom;
    }
    else if (isRight(halign) && isTop(valign))
    {
        layout = TextLayout::RightTop;
    }
    else if (isRight(halign) && isCenter(valign))
    {
        layout = TextLayout::RightCenter;
    }
    else if (isRight(halign) && isBottom(valign))
    {
        layout = TextLayout::RightBottom;
    }

    return layout;
}

Color32 TmxSceneLoader::getTextColor(const TmxText *text) const
{
    auto hexColor = text->color();
    auto intColor = strtol(hexColor + 1, nullptr, 16);

    auto r = (byte)((intColor >> 16) & 0xFF);
    auto g = (byte)((intColor >> 8) & 0xFF);
    auto b = (byte)(intColor & 0xFF);

    return Color32(r, g, b);
}
