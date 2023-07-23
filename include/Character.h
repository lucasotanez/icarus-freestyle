#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"
#include "Animations.h"

class Character : public Entity{
    public:
        Character(Vector2f p_pos, SDL_Texture* p_tex, int w, int h, 
                Animation& walkR, Animation& walkL);
        void movePos(int speed, char dir);
        void setPos(int x, int y);
        void jump();
        void playAnimation(Animation*, float timestamp, float frameLength);

        float lastAction;

    private:
        Animation* walkRight;
        Animation* walkLeft;
        bool inAir;

};

#endif