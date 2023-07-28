#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.h"
#include "Animations.h"

struct Hitbox {
    Hitbox(uint8_t x, uint8_t y) : marginX(x), marginY(y) {};
    uint8_t marginX, marginY;
};

class Entity{
    public:
        Entity(Vector2f p_pos, SDL_Texture* p_tex, int width, int height);
        virtual ~Entity(){};
        Vector2f& getPos();
        SDL_Texture* getTex();
        SDL_Rect getCurrFrame();

        virtual void movePos(float speedX, float speedY) = 0;
        virtual void playAnimation(Animation*, float timestamp, float frameLength) = 0;
        void changeTex(SDL_Texture* newTex);

        bool collides(Entity& ent);
    protected:
        Vector2f pos; // top left corner
        SDL_Rect currentFrame;
        Hitbox hitbox;
        SDL_Texture* tex;

};

#endif
