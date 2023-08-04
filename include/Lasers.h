#ifndef LASERS_H
#define LASERS_H
#include "Math.h"
#include "Entity.h"
#include "Game.h"

class LaserVertical : public Entity {
    public:
        LaserVertical(Vector2f pos, Assets* assets);
};

class LaserHorizontal : public Entity {
    public:
        LaserHorizontal(Vector2f pos, Assets* assets);
};

class LaserNegativeSlope : public Entity {
    public:
        LaserNegativeSlope(Vector2f pos, Assets* assets);
        bool collides(const Entity &ent) const override;
};

class LaserPositiveSlope : public Entity {
    public:
        LaserPositiveSlope(Vector2f pos, Assets* assets);
        bool collides(const Entity &ent) const override;
};


#endif
