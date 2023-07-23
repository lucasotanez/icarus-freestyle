#include "Character.h"

Character::Character(Vector2f p_pos, SDL_Texture* p_tex, int w, int h, Animation& walkR, Animation& walkL)
    : Entity(p_pos, p_tex, w, h), inAir(false), walkRight(&walkR), walkLeft(&walkL), lastAction(0)
{}

void Character::movePos(int speed, char dir){
    if (dir == 'E'){
        pos.x += speed;
    }
    if (dir == 'W'){
        pos.x -= speed;
    }
    if (dir == 'N'){
        pos.y -= speed;
    }
    if (dir == 'S'){
        pos.y += speed;
    }
}

void Character::setPos(int x, int y)
{
    pos.x = x;
    pos.y = y;
}

void Character::jump(){
    inAir = true;
    
}

void Character::playAnimation(Animation* anim, float timestamp, float frameLength){
    //TODO
    if (timestamp - lastAction >= frameLength /*animation speed*/){
        if (anim->step_ == anim->numFrames()-1){
            anim->step_ = 0;
        }
        else anim->step_++;
        changeTex((*anim)[anim->step_]);
        lastAction = timestamp;
    }
}