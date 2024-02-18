#ifndef START_H
#define START_H

#include <vector>
// Fix error regarding "expected primary-expression before ')' token
#undef __STRICT_ANSI__
#include "impl/Engine/sprite_collider.h"
#include "impl/Engine/sprite.h"

class Start {
public:
    Start();
    bool update(int keys[], float dt, float t);
    bool draw();
    ~Start();
private:
    std::vector<Sprite*> draw_sprites;
    SpriteCollider sprite_collider;
};

#endif // START_H
