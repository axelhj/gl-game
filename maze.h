#ifndef MAZE_H
#define MAZE_H

#include "mat4.h"
#include "sprite.h"
#include "text_sprite.h"
#include "sprite_collider.h"
#include "a_star.h"

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
};

#endif // MAZE_H
