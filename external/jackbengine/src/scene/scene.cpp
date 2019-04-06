//
// scene.cpp
// jackbengine
//
// Created by Damien Bendejacq on 09/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "scene.hpp"

using namespace Jackbengine;

Scene::Scene(Application& application, SceneManager<Scene>& sceneManager)
    : m_application {application},
      m_sceneManager {sceneManager},
      m_systemManager {m_entityManager}
{ }

Entity Scene::addEntity()
{
    return m_entityManager.addEntity();
}

void Scene::removeEntity(Entity entity)
{
    m_entityManager.removeEntity(entity);
    m_systemManager.removeEntity(entity, false);
}

void Scene::enableEntity(Entity entity)
{
    enableEntity(entity, true);
}

void Scene::enableEntity(Entity entity, bool enable)
{
    m_entityManager.enableEntity(entity, enable);

    if (enable)
    {
        m_systemManager.addEntity(entity);
    }
    else
    {
        m_systemManager.removeEntity(entity, false);
    }
}

void Scene::disableEntity(Entity entity)
{
    enableEntity(entity, false);
}

void Scene::update(float delta)
{
    m_systemManager.frame(delta);
    frame(delta);
    m_sceneManager.trySetNextScene();
}

Timer& Scene::timer() const
{
    return m_application.timer();
}

Cursor& Scene::cursor() const
{
    return m_application.cursor();
}

Input& Scene::input() const
{
    return m_application.input();
}

Window& Scene::window() const
{
    return m_application.window();
}

Renderer& Scene::renderer() const
{
    return m_application.renderer();
}

void Scene::exitApplication()
{
    m_application.exit();
}

void Scene::frame(float)
{ }
