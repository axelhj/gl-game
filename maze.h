#ifndef MAZE_H
#define MAZE_H

#include "mat4.h"
#include "sprite.h"
#include "text_sprite.h"
#include "sprite_collider.h"
#include "a_star.h"

extern bool init_maze();

extern bool update_maze(int keys[], float dt, float t);

extern bool draw_maze();

extern bool destroy_maze();

#endif // MAZE_H
