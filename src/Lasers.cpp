#include "Lasers.h"

LaserVertical::LaserVertical(Vector2f pos, Assets* assets)
    : Entity(pos, &assets->laserY1, Hitbox(4, 8), &assets->laserIdleY)
{}

LaserVertical::LaserVertical()
    : Entity()
{}

LaserHorizontal::LaserHorizontal(Vector2f pos, Assets* assets)
    : Entity(pos, &assets->laserX1, Hitbox(8, 4), &assets->laserIdleX)
{}

LaserNegativeSlope::LaserNegativeSlope(Vector2f pos, Assets* assets)
    : Entity(pos, &assets->laserNegS1, Hitbox(8,8), &assets->laserIdleNS)
{
    
}

bool LaserNegativeSlope::collides(const Entity &ent) const {
    // hitbox dimensions should be square for this class of laser
    if (ent.getHitbox()->marginX != ent.getHitbox()->marginY) return false;

    // hitbox buffers
    float entLeft = ent.getPos().x + ((float)ent.getCurrFrame().w/ent.getHitbox()->marginX);
    float entRight = ent.getPos().x + ent.getCurrFrame().w - ((float)ent.getCurrFrame().w/ent.getHitbox()->marginX);
    float entTop = ent.getPos().y + ((float)ent.getCurrFrame().h/ent.getHitbox()->marginY);
    float entBot = ent.getPos().y + ent.getCurrFrame().h - ((float)ent.getCurrFrame().h/ent.getHitbox()->marginY);

    float thisLeft = this->getPos().x + (float)this->getCurrFrame().w/this->getHitbox()->marginX;
    float thisRight = this->getPos().x + this->getCurrFrame().w - (float)this->getCurrFrame().w/this->getHitbox()->marginX;
    float thisBot = this->getPos().y + this->getCurrFrame().h - (float)this->getCurrFrame().h/this->getHitbox()->marginY;
    float thisTop = this->getPos().y + (float)this->getCurrFrame().h/this->getHitbox()->marginY;

    if (thisLeft > entRight || thisRight < entLeft) return false;
    if (thisTop > entBot || thisBot < entTop) return false;
    int vertScale = this->getCurrFrame().w - (this->getCurrFrame().w + thisLeft - entLeft);
    int passingY = thisTop + vertScale;
    if (passingY > entTop && passingY < entBot){
        return true;
    } else return false;
}

LaserPositiveSlope::LaserPositiveSlope(Vector2f pos, Assets* assets)
    : Entity(pos, &assets->laserPosS1, Hitbox(8, 8), &assets->laserIdlePS)
{}

bool LaserPositiveSlope::collides(const Entity &ent) const {
    // hitbox dimensions should be square for this class of laser
    if (ent.getHitbox()->marginX != ent.getHitbox()->marginY) return false;

    // hitbox buffers
    float entLeft = ent.getPos().x + ((float)ent.getCurrFrame().w/ent.getHitbox()->marginX);
    float entRight = ent.getPos().x + ent.getCurrFrame().w - ((float)ent.getCurrFrame().w/ent.getHitbox()->marginX);
    float entTop = ent.getPos().y + ((float)ent.getCurrFrame().h/ent.getHitbox()->marginY);
    float entBot = ent.getPos().y + ent.getCurrFrame().h - ((float)ent.getCurrFrame().h/ent.getHitbox()->marginY);

    float thisLeft = this->getPos().x + (float)this->getCurrFrame().w/this->getHitbox()->marginX;
    float thisRight = this->getPos().x + this->getCurrFrame().w - (float)this->getCurrFrame().w/this->getHitbox()->marginX;
    float thisBot = this->getPos().y + this->getCurrFrame().h - (float)this->getCurrFrame().h/this->getHitbox()->marginY;
    float thisTop = this->getPos().y + (float)this->getCurrFrame().h/this->getHitbox()->marginY;

    if (thisLeft > entRight || thisRight < entLeft) return false;
    if (thisTop > entBot || thisBot < entTop) return false;
    int vertScale = this->getCurrFrame().w - (this->getCurrFrame().w + thisLeft - entLeft);
    int passingY = thisBot - vertScale;
    if (passingY > entTop && passingY < entBot){
        return true;
    } else return false;
}

