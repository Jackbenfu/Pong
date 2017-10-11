//
//  main.cpp
//  Pong
//
//  Created by Damien Bendejacq on 24/10/14.
//  Copyright © 2014 Damien Bendejacq. All rights reserved.
//

#include "app.hpp"

#ifdef EMSCRIPTEN
    #include <emscripten.h>
#endif

#define FULLSCREEN_OPTION   "-fullscreen"

using namespace Jackbengine;

void parseArguments(int argc, char **argv, bool *fullscreen)
{
    for (auto i = 1; i < argc; ++i)
    {
        auto arg = argv[i];
        if (strstr(arg, FULLSCREEN_OPTION) == arg)
        {
            *fullscreen = true;
        }
    }
}

#ifdef EMSCRIPTEN

App *appPtr;
void loop()
{
    appPtr->loop();
}

#endif

int main(int argc, char **argv)
{
    auto fullscreen = false;
    parseArguments(argc, argv, &fullscreen);

    ApplicationConfig config { "Pong", 768, 576, fullscreen };
    App app(config);

#ifdef EMSCRIPTEN
    appPtr = &app;
    emscripten_set_main_loop(loop, 0, 1);
#else
    while (app.running())
    {
        app.loop();
    }
#endif

    return 0;
}
