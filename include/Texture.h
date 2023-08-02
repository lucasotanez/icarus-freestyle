#ifndef TEXTURE_H
#define TEXTURE_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

class Texture {
    public:
        Texture();

        ~Texture();

        bool loadFromFile(const char* path );

        bool loadFromText(const char* text, SDL_Color color, int size);

        void free();

        // getters
        int getWidth() { return _width; };
        int getHeight() { return _height; };
        SDL_Texture* getTex() { return _texture; };

    private:
        SDL_Texture* _texture;

        int _width;
        int _height;

};

#endif
