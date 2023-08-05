#ifndef ANIMATIONS_H
#define ANIMATIONS_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Texture.h"

class Animation
{
    public:
        Animation();
        void addFrame(Texture* newF);
        //SDL_Texture* operator[](int idx);
        Texture* operator[](int idx);
        uint8_t numFrames();
        //uint8_t getStep();
        uint8_t step;

    private:
        //FRAMES: Art needed (frames loaded in main.cpp)
        //==================================================================
        //Animation will cycle from last frame back to first frame:
        //e.g. 0,1,2,3,0,1,2,3,0,1,2 ... (see Entity & relevant subclasses)
        std::vector<Texture*> _frames;
        //==================================================================

};


#endif
