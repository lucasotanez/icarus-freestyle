#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>

namespace utils
{
    inline float timeInSeconds()
    {
        float t = SDL_GetTicks();
        t *= 0.001;
        return t;
    }
}

#endif