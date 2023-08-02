#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.h"
#include "Animations.h"
#include "Texture.h"

struct Hitbox {
    Hitbox(uint8_t x, uint8_t y) : marginX(x), marginY(y) {};
    int8_t marginX, marginY;
};

class Entity{
    public:
        Entity(Vector2f p_pos, Texture* p_tex, Hitbox hb = Hitbox(4, 4));
        virtual ~Entity(){};
        const Vector2f& getPos() const;
        Texture* getTex() const;
        const SDL_Rect& getCurrFrame() const;
        virtual const Hitbox& getHitbox() const; 

        virtual void movePos(float speedX, float speedY) = 0;
        virtual void playAnimation(Animation*, float timestamp, float frameLength) = 0;
        void playIdleAnim(float timestamp, float frameLength) const;

        void changeTex(Texture* newTex);

        virtual bool collides(const Entity& ent) const;
    protected:
        Vector2f pos; // top left corner
        SDL_Rect currentFrame;
        Hitbox hitbox;
        //SDL_Texture* tex;
        Texture* tex;
        Animation* idleAnim;

};

#endif
