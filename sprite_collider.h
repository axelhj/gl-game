#ifndef SPRITE_COLLIDER
#define SPRITE_COLLIDER

#include <math.h>
#include <float.h>
#include "sprite.h"

class SpriteCollider {
public:
    SpriteCollider();
    bool add_sprites(Sprite** sprites, int count);
    bool process_sprites(float dt);
    void remove_sprites();
    ~SpriteCollider();
private:
    Sprite** sprites;
    int sprite_count;
};

#endif // SPRITE_COLLIDER
