//
// scene.hpp
// jackbengine
//
// Created by Damien Bendejacq on 09/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __SCENE_H__
#define __SCENE_H__

#include "sceneManager.hpp"
#include "application/application.hpp"
#include "entity/entityManager.hpp"
#include "system/systemManager.hpp"

namespace Jackbengine {

class Scene
{
    DISALLOW_COPY_AND_MOVE(Scene)

public:
    Scene(Application& application, SceneManager<Scene>& sceneManager);
    virtual ~Scene() = default;

    /*
     * Entity
     */
    Entity addEntity();
    void removeEntity(Entity entity);
    void enableEntity(Entity entity);
    void enableEntity(Entity entity, bool enable);
    void disableEntity(Entity entity);

    /*
     * Component
     */
    template<typename TComponent, typename ...Args>
    void addComponent(Entity entity, Args&& ...args);

    template<typename TComponent>
    void removeComponent(Entity entity);

    template<typename TComponent>
    TComponent& getComponent(Entity entity) const;

    template<typename TComponent>
    void enableComponent(Entity entity);

    template<typename TComponent>
    void enableComponent(Entity entity, bool enable);

    template<typename TComponent>
    void disableComponent(Entity entity);

    /*
     * System
     */
    template<typename TSystem, typename ...Args>
    void addSystem(Args&& ...args);

    template<typename TSystem>
    void removeSystem();

    template<typename TSystem>
    TSystem& getSystem();

    template<typename TSystem>
    void enableSystem();

    template<typename TSystem>
    void enableSystem(bool enable);

    template<typename TSystem>
    void disableSystem();

    void update(float delta);

    Timer& timer() const;
    Cursor& cursor() const;
    Input& input() const;
    Window& window() const;
    Renderer& renderer() const;

    void exitApplication();

    template<typename TScene>
    void loadScene();

private:
    virtual void frame(float delta);

    Application& m_application;
    SceneManager<Scene>& m_sceneManager;
    EntityManager m_entityManager;
    SystemManager m_systemManager;
};

template<typename TComponent, typename ...Args>
void Scene::addComponent(Entity entity, Args&& ...args)
{
    m_entityManager.addComponent<TComponent>(entity, std::forward<Args>(args)...);
    m_systemManager.addEntity(entity);
}

template<typename TComponent>
void Scene::removeComponent(Entity entity)
{
    m_entityManager.removeComponent<TComponent>(entity);
    m_systemManager.removeEntity(entity, true);
}

template<typename TComponent>
TComponent& Scene::getComponent(Entity entity) const
{
    return m_entityManager.getComponent<TComponent>(entity);
}

template<typename TComponent>
void Scene::enableComponent(Entity entity)
{
    enableComponent<TComponent>(entity, true);
}

template<typename TComponent>
void Scene::enableComponent(Entity entity, bool enable)
{
    m_entityManager.enableComponent<TComponent>(entity, enable);
    if (enable)
    {
        m_systemManager.addEntity(entity);
    }
    else
    {
        m_systemManager.removeEntity(entity, true);
    }
}

template<typename TComponent>
void Scene::disableComponent(Entity entity)
{
    enableComponent<TComponent>(entity, false);
}

template<typename TSystem, typename ...Args>
void Scene::addSystem(Args&& ...args)
{
    m_systemManager.addSystem<TSystem>(std::forward<Args>(args)...);
}

template<typename TSystem>
void Scene::removeSystem()
{
    m_systemManager.removeSystem<TSystem>();
}

template<typename TSystem>
TSystem& Scene::getSystem()
{
    return m_systemManager.getSystem<TSystem>();
}

template<typename TSystem>
void Scene::enableSystem()
{
    enableSystem<TSystem>(true);
}

template<typename TSystem>
void Scene::enableSystem(bool enable)
{
    m_systemManager.enableSystem<TSystem>(enable);
}

template<typename TSystem>
void Scene::disableSystem()
{
    enableSystem<TSystem>(false);
}

template<typename TScene>
void Scene::loadScene()
{
    static_assert(std::is_base_of<Scene, TScene>::value);

    m_sceneManager.loadScene<TScene>(m_application, m_sceneManager);
}

} // namespace Jackbengine

#endif // __SCENE_H__
