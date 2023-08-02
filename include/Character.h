#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"
#include "Animations.h"
#include "Texture.h"

class Character : public Entity{
    public:
        Character(Vector2f p_pos, Texture* p_tex, Hitbox hb = Hitbox(4, 4), Animation* idle = nullptr);
        void movePos(float speedX, float speedY);
        void setPos(int x, int y);
        void setPosX(int x);
        void setPosY(int y);
        void jump();
        void playAnimation(Animation*, float timestamp, float frameLength);
        void playIdleAnim(float timestamp, float frameLength);

        bool collides(const Entity& ent) const;

        float lastAction;

    private:
        bool inAir;
        Animation* idleAnim;

};

#endif
