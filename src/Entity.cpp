#include "Entity.h"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, int width, int height, Hitbox hb)
    : pos(p_pos), tex(p_tex) , hitbox(hb)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = width/*32*/;
    currentFrame.h = height/*32*/;

}

const Vector2f& Entity::getPos() const{
    return pos;
}

SDL_Texture* Entity::getTex() const {
    return tex;
}

const SDL_Rect& Entity::getCurrFrame() const{
    return currentFrame;
}

const Hitbox& Entity::getHitbox() const {
    return hitbox;
}


void Entity::changeTex(SDL_Texture* newTex){
    if (tex == newTex) return; //nothing to do
    tex = newTex;
}

bool Entity::collides(const Entity& ent) const {

    // if one entity is to the right of the other
    if (ent.pos.x + ent.currentFrame.w < this->pos.x) return false;
    if (this->pos.x + this->currentFrame.w < ent.pos.x) return false;

    //if one entity is below the other
    if (ent.pos.y + ent.currentFrame.h < this->pos.y) return false;
    if (this->pos.y + this->currentFrame.h < ent.pos.y) return false;

    // else...
    return true;
}
