//
//  main.cpp
//  Pong
//
//  Created by Damien Bendejacq on 24/10/14.
//  Copyright (c) 2014 Damien Bendejacq. All rights reserved.
//

#include "pongApp.h"

#define FULLSCREEN_OPTION   "-fullscreen"

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

int main(int argc, char **argv)
{
    UNUSED(argc)
    UNUSED(argv)

    bool fullscreen = false;
    parseArguments(argc, argv, &fullscreen);

    PongApp app(fullscreen);
    return app.run();
}
