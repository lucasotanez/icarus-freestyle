#include "Character.h"

Character::Character(Vector2f p_pos, Texture* tex, Hitbox hb, Animation* idle)
    : Entity(p_pos, tex, hb, idle)
{}

void Character::movePos(float speed, float){
    _pos.y -= speed;
}

//void Character::playAnimation(Animation* anim, float timestamp, float frameLength){
//    if (timestamp - anim->lastFrame >= frameLength /*animation speed*/){
//        if (anim->step_ == anim->numFrames()-1){
//            anim->step_ = 0;
//        }
//        else anim->step_++;
//        changeTex((*anim)[anim->step_]);
//        anim->lastFrame = timestamp;
//    }
//}

