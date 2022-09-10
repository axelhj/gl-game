#ifndef START_H
#define START_H

#include <vector>

#include "impl/Util/mat4.h"
#include "impl/Engine/sprite_collider.h"
#include "impl/Engine/sprite.h"
#include "impl/Engine/text_sprite.h"

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
