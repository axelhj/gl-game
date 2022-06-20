#ifndef MAZE_H
#define MAZE_H

#include "impl/Util/mat4.h"
#include "impl/Util/a_star.h"
#include "impl/Engine/sprite.h"
#include "impl/Engine/text_sprite.h"
#include "impl/Engine/sprite_collider.h"

#define TILES_X 12
#define TILES_Y 9

#define DRAW_SPRITES_COUNT 37

class Maze {
public:
    Maze();
    bool update(int keys[], float dt, float t);
    bool draw();
    ~Maze();
private:
    Sprite* draw_sprites[DRAW_SPRITES_COUNT];
    Sprite* tiles[TILES_X * TILES_Y];
    SpriteCollider spriteCollider;
};

#endif // MAZE_H
