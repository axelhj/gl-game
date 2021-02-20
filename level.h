#ifndef LEVEL_H
#define LEVEL_H

#include "mat4.h"
#include "sprite.h"
#include "sprite_collider.h"

extern bool init_level();

extern bool update_level(int keys[], float dt, float t);

extern bool draw_level();

extern bool destroy_level();

#endif // LEVEL_H
