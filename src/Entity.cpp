#include "Entity.h"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, int width, int height)
    : pos(p_pos), tex(p_tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = width/*32*/;
    currentFrame.h = height/*32*/;
}

Vector2f& Entity::getPos(){
    return pos;
}

SDL_Texture* Entity::getTex(){
    return tex;
}

SDL_Rect Entity::getCurrFrame(){
    return currentFrame;
}

void Entity::changeTex(SDL_Texture* newTex){
    if (tex == newTex) return; //nothing to do
    tex = newTex;
}


bool Entity::collides(Entity& ent){

    // if one entity is to the right of the other
    if (ent.pos.x + ent.currentFrame.w < this->pos.x) return false;
    if (this->pos.x + this->currentFrame.w < ent.pos.x) return false;

    //if one entity is below the other
    if (ent.pos.y + ent.currentFrame.h < this->pos.y) return false;
    if (this->pos.y + this->currentFrame.h < ent.pos.y) return false;

    // else...
    return true;
}
