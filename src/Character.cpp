#include "Character.h"

Character::Character(Vector2f p_pos, SDL_Texture* p_tex, int w, int h, Hitbox hb, Animation* idle)
    : Entity(p_pos, p_tex, w, h, hb), inAir(false), lastAction(0), idleAnim(idle)
{}

void Character::movePos(float speedX, float speedY){
    pos.x += speedX;
    pos.y -= speedY;
}

void Character::setPos(int x, int y)
{
    pos.x = x;
    pos.y = y;
}

void Character::setPosX(int x)
{
    pos.x = x;
}

void Character::setPosY(int y)
{
    pos.y = y;
}

void Character::jump(){
    inAir = true;
}


void Character::playAnimation(Animation* anim, float timestamp, float frameLength){
    if (timestamp - lastAction >= frameLength /*animation speed*/){
        if (anim->step_ == anim->numFrames()-1){
            anim->step_ = 0;
        }
        else anim->step_++;
        changeTex((*anim)[anim->step_]);
        lastAction = timestamp;
    }
}

void Character::playIdleAnim(float timestamp, float frameLength) {
    if (timestamp - lastAction >= frameLength /*animation speed*/){
        if (idleAnim->step_ == idleAnim->numFrames()-1){
            idleAnim->step_ = 0;
        }
        else idleAnim->step_++;
        changeTex((*idleAnim)[idleAnim->step_]);
        lastAction = timestamp;
    }
}

bool Character::collides(const Entity& ent) const {

    int thisBufH, thisBufW, entBufH, entBufW;
    thisBufH = this->currentFrame.h / this->hitbox.marginY;
    thisBufW = this->currentFrame.w / this->hitbox.marginX;
    entBufH = ent.getCurrFrame().h / ent.getHitbox().marginY;
    entBufW = ent.getCurrFrame().w / ent.getHitbox().marginX;

    // if one entity is to the right of the other
    if (ent.getPos().x + ent.getCurrFrame().w - entBufW < this->pos.x + thisBufW) return false;
    if (this->pos.x + this->currentFrame.w - thisBufW < ent.getPos().x + entBufW) return false;

    //if one entity is below the other
    if (ent.getPos().y + ent.getCurrFrame().h - entBufH < this->pos.y + thisBufH) return false;
    if (this->pos.y + this->currentFrame.h - thisBufH < ent.getPos().y + entBufH) return false;

    // else...
    return true;
}
