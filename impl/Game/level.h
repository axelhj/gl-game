#ifndef LEVEL_H
#define LEVEL_H

#include "impl/Engine/sprite_collider.h"
#include "impl/Engine/sprite.h"

#define TILES_X 12
#define TILES_Y 9

#define DRAW_SPRITES_COUNT 36

class Level {
public:
    Level();
    bool update(int keys[], float dt, float t);
    bool draw();
    ~Level();
private:
    Sprite* draw_sprites[DRAW_SPRITES_COUNT];
    Sprite* tiles[TILES_X * TILES_Y];
    SpriteCollider sprite_collider;
};

#endif // LEVEL_H
