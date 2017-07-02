//
// gameSceneLoader.h
// Pong
//
// Created by Damien Bendejacq on 17/09/2016.
// Copyright © 2016 Damien Bendejacq. All rights reserved.
//

#ifndef __GAME_SCENE_LOADER_H__
#define __GAME_SCENE_LOADER_H__

#include "jackbengine.hpp"

class GameSceneLoader : public Jackbengine::TmxSceneLoader
{
public:
    explicit GameSceneLoader(Jackbengine::Scene *scene);
    ~GameSceneLoader() override;

    int getMaxScore() const;

private:
    bool loadContents() override;

    void loadSystems();

    // Level loading
    void loadWall(const char *name);
    void loadPaddle(const char *name, const void *soundData, size_t soundDataSize);
    void loadBall();
    void loadScore(const char *name);
    void loadGameOver();
    void loadResult(const char *name);

    static const int GOAL2_TEXT_SIZE = 30;
    char m_goal2Text[GOAL2_TEXT_SIZE];

    const char *TILESET_FILE = "tileset.png";
};

#endif // __GAME_SCENE_LOADER_H__
