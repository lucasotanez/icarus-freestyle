#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.h"
#include "Animations.h"
#include "Texture.h"

struct Hitbox {
    inline Hitbox(uint8_t x, uint8_t y) : marginX(x), marginY(y) {};
    int8_t marginX, marginY;
};

class Entity{
    public:
        Entity(Vector2f p_pos, Texture* p_tex, Hitbox hb = Hitbox(0, 0), Animation* idle = NULL);
        virtual ~Entity();
        const Vector2f& getPos() const;
        Texture* getTex() const;
        const SDL_Rect& getCurrFrame() const;
        virtual const Hitbox* getHitbox() const; 

        void setPos(int x, int y);
        void setPosX(int x);
        void setPosY(int y);
        virtual void movePos(float speedX, float speedY);

        void playIdleAnim(float timestamp, float frameLength);

        void changeTex(Texture* newTex);

        virtual bool collides(const Entity& ent) const;
    protected:
        float _lastFrame; // timestamp of last animation frame
        Vector2f _pos; // top left corner
        SDL_Rect _currentFrame;
        Hitbox _hitbox;
        Texture* _tex;
        Animation* _idleAnim;

};

#endif
