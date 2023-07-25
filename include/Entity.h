#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.h"

class Entity{
    public:
        Entity(Vector2f p_pos, SDL_Texture* p_tex, int width, int height);
        Vector2f& getPos();
        SDL_Texture* getTex();
        SDL_Rect getCurrFrame();

        void changeTex(SDL_Texture* newTex);

        bool collides(Entity& ent);
    protected:
        Vector2f pos; // top left corner
        SDL_Rect currentFrame;
        SDL_Rect hitbox;
        SDL_Texture* tex;

};

#endif
