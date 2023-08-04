#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"
#include "Animations.h"
#include "Texture.h"

class Character : public Entity{
    public:
        Character(Vector2f p_pos, Texture* p_tex, Hitbox hb = Hitbox(4, 4), Animation* idle = nullptr);
        Character();
        void movePos(float speed, float nullSpeed = 0) override;

        // TODO: create functions to play stored animations

    private:
        Animation* _runAnim;
        Animation* _hoverAnim;
        Animation* _deathAnim;

};

#endif
