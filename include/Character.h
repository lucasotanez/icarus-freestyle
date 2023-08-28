#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"
#include "Animations.h"
#include "Texture.h"

class Character : public Entity{
    public:
        Character(Vector2f p_pos, Texture* p_tex, Hitbox hb = Hitbox(4, 4), Animation* idle = nullptr, Animation* run = nullptr);
        Character();
        void movePos(float speed, float nullSpeed = 0) override;
        void playRunAnim(float timestamp, float frameLength);

        // TODO: create functions to play stored animations

    private:
        Animation* _runAnim;

};

#endif
