#include "Entity.h"

Entity::Entity(Vector2f pos, Texture* p_tex, Hitbox hb, Animation* idle, int scale)
    : _pos(pos), _tex(p_tex) , _hitbox(hb), _idleAnim(idle), _scaleF(scale)
{
    _currentFrame.x = 0;
    _currentFrame.y = 0;
    _currentFrame.w = p_tex->getWidth() * _scaleF;
    _currentFrame.h = p_tex->getHeight() * _scaleF;
}

Entity::Entity(Vector2f pos)
    : _pos(pos), _tex(NULL), _hitbox(Hitbox(0,0)), _idleAnim(NULL), _scaleF(3)
{
    _currentFrame.x = 0;
    _currentFrame.y = 0;
    _currentFrame.w = 0;
    _currentFrame.h = 0;
}

Entity::Entity()
    : _pos(0, 0), _tex(NULL), _hitbox(Hitbox(0,0)), _idleAnim(NULL), _scaleF(3)
{
    _currentFrame.x = 0;
    _currentFrame.y = 0;
    _currentFrame.w = 0;
    _currentFrame.h = 0;
}

Entity::~Entity(){}

const Vector2f& Entity::getPos() const{
    return _pos;
}

Texture* Entity::getTex() const {
    return _tex; 
}

const SDL_Rect& Entity::getCurrFrame() const{
    return _currentFrame;
}

const Hitbox* Entity::getHitbox() const {
    if (_hitbox.marginY == 0 || _hitbox.marginX == 0) return NULL;
    return &_hitbox;
}

void Entity::setPos(Vector2f newPos) {
    _pos.x = newPos.x;
    _pos.y = newPos.y;
}

void Entity::setPos(int x, int y)
{
    _pos.x = x;
    _pos.y = y;
}

void Entity::setPosX(int x)
{
    _pos.x = x;
}

void Entity::setPosY(int y)
{
    _pos.y = y;
}

void Entity::movePos(float speedX, float speedY) {
    _pos.x += speedX;
    _pos.y += speedY;
}

void Entity::playIdleAnim(float timestamp, float frameLength) {
    if (_idleAnim != NULL) {
        if (timestamp - _lastFrame >= frameLength /*animation speed*/){
            if (_idleAnim->step == (_idleAnim->numFrames())-1){
                _idleAnim->step = 0;
            }
            else _idleAnim->step++;

            changeTex((*_idleAnim)[_idleAnim->step]);
            _lastFrame = timestamp;
        }
    }
}

void Entity::playRunAnim(float timestamp, float frameLength) {
    return;
}

void Entity::changeTex(Texture* newTex){
    if (_tex == newTex) return; //nothing to do
    _tex = newTex;
    _currentFrame.w = _tex->getWidth() * _scaleF;
    _currentFrame.h = _tex->getHeight() * _scaleF;
}

bool Entity::collides(const Entity& ent) const {

    int thisBufH, thisBufW, entBufH, entBufW;

    if (ent.getHitbox() == NULL){
        entBufH = entBufW = 0;
    } else {
        entBufH = ent.getCurrFrame().h / ent.getHitbox()->marginY;
        entBufW = ent.getCurrFrame().w / ent.getHitbox()->marginX;
    }

    if (this->getHitbox() == NULL){
        thisBufH = thisBufW = 0;
    } else {
        thisBufH = this->_currentFrame.h / this->_hitbox.marginY;
        thisBufW = this->_currentFrame.w / this->_hitbox.marginX;
    }

    // if one entity is to the right of the other
    if (ent.getPos().x + ent.getCurrFrame().w - entBufW < this->_pos.x + thisBufW) return false;
    if (this->_pos.x + this->_currentFrame.w - thisBufW < ent.getPos().x + entBufW) return false;

    // if one entity is below the other
    if (ent.getPos().y + ent.getCurrFrame().h - entBufH < this->_pos.y + thisBufH) return false;
    if (this->_pos.y + this->_currentFrame.h - thisBufH < ent.getPos().y + entBufH) return false;

    // else...
    return true;
}
