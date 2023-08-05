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
        Entity(Vector2f pos, Texture* p_tex = NULL, Hitbox hb = Hitbox(0, 0), Animation* idle = NULL);
        Entity(Vector2f pos);
        Entity();
        virtual ~Entity();
        const Vector2f& getPos() const;
        const SDL_Rect& getCurrFrame() const;
        virtual const Hitbox* getHitbox() const; 

        void setPos(Vector2f newPos);
        void setPos(int x, int y);
        void setPosX(int x);
        void setPosY(int y);
        virtual void movePos(float speedX, float speedY);

        void playIdleAnim(float timestamp, float frameLength);

        void changeTex(Texture* newTex);
        Texture* getTex() const;

        virtual bool collides(const Entity& ent) const;

        inline int getScale() { return _scaleF; };
    protected:
        int _scaleF = 3;
        float _lastFrame; // timestamp of last animation frame
        Vector2f _pos; // top left corner
        SDL_Rect _currentFrame;
        Hitbox _hitbox;
        Texture* _tex;
        Animation* _idleAnim;

};

#endif
