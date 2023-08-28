#include "Character.h"

Character::Character(Vector2f p_pos, Texture* tex, Hitbox hb, Animation* idle, Animation* run)
    : Entity(p_pos, tex, hb, idle)
{}

Character::Character()
    : Entity(), _runAnim(NULL) 
{}

void Character::playRunAnim(float timestamp, float frameLength) {
    if (_runAnim != NULL) {
        if (timestamp - _lastFrame >= frameLength /*animation speed*/){
            if (_runAnim->step == (_runAnim->numFrames())-1){
                _runAnim->step = 0;
            }
            else _runAnim->step++;

            changeTex((*_runAnim)[_runAnim->step]);
            _lastFrame = timestamp;
        }
    }
}

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

