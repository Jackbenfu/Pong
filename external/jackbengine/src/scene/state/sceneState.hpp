//
// sceneState.hpp
// jackbengine
//
// Created by Damien Bendejacq on 15/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __SCENE_STATE_H__
#define __SCENE_STATE_H__

#include "../scene.hpp"
#include "core/state/state.hpp"

namespace Jackbengine {

class SceneState : public State
{
    DISALLOW_COPY_AND_MOVE(SceneState)

public:
    SceneState(StateMachine& stateMachine, Scene& scene)
        : State(stateMachine),
          m_scene {scene}
    { }

    ~SceneState() override = default;

protected:
    template<typename TState>
    inline void goToState() { stateMachine().goToState<TState>(); }

    inline Entity addEntity() { return m_scene.addEntity(); }
    inline void removeEntity(Entity entity) { m_scene.removeEntity(entity); }
    inline void enableEntity(Entity entity) { m_scene.enableEntity(entity); }
    inline void enableEntity(Entity entity, bool enable) { m_scene.enableEntity(entity, enable); }
    inline void disableEntity(Entity entity) { m_scene.disableEntity(entity); }

    template<typename TComponent, typename ...Args>
    inline void addComponent(Entity entity, Args&& ...args) { m_scene.addComponent<TComponent>(entity, std::forward<Args>(args)...); }

    template<typename TComponent>
    inline void removeComponent(Entity entity) { m_scene.removeComponent<TComponent>(entity); }

    template<typename TComponent>
    inline TComponent& getComponent(Entity entity) const { return m_scene.getComponent<TComponent>(entity); }

    template<typename TComponent>
    inline void enableComponent(Entity entity) { m_scene.enableComponent<TComponent>(entity); }

    template<typename TComponent>
    inline void enableComponent(Entity entity, bool enable) { m_scene.enableComponent<TComponent>(entity, enable); }

    template<typename TComponent>
    inline void disableComponent(Entity entity) { m_scene.disableComponent<TComponent>(entity); }

    template<typename TSystem, typename ...Args>
    inline void addSystem(Args&& ...args) { m_scene.addSystem<TSystem>(std::forward<Args>(args)...); }

    template<typename TSystem>
    inline void removeSystem() { m_scene.removeSystem<TSystem>(); }

    template<typename TSystem>
    inline TSystem& getSystem() { return m_scene.getSystem<TSystem>(); }

    template<typename TSystem>
    inline void enableSystem() { m_scene.enableSystem<TSystem>(); }

    template<typename TSystem>
    inline void enableSystem(bool enable) { m_scene.enableSystem<TSystem>(enable); }

    template<typename TSystem>
    inline void disableSystem() { m_scene.disableSystem<TSystem>(); }

    inline Timer& timer() const { return m_scene.timer(); }
    inline Cursor& cursor() const { return m_scene.cursor(); }
    inline Input& input() const { return m_scene.input(); }
    inline Window& window() const { return m_scene.window(); }
    inline Renderer& renderer() const { return m_scene.renderer(); }

    inline void exitApplication() { m_scene.exitApplication(); }

    template<typename TScene>
    inline void loadScene() { m_scene.loadScene<TScene>(); }

private:
    Scene& m_scene;
};

} // namespace Jackbengine

#endif // __SCENE_STATE_H__
