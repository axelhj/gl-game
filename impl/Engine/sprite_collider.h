#ifndef SPRITE_COLLIDER
#define SPRITE_COLLIDER

#include <vector>
#include "impl/Engine/sprite.h"

using std::vector;

class SpriteCollider {
public:
    SpriteCollider();
    bool add_sprites(vector<Sprite*> sprites);
    bool process_sprites(float dt);
    void remove_sprites();
    ~SpriteCollider();
private:
    vector<Sprite*> sprites;
};

#endif // SPRITE_COLLIDER
