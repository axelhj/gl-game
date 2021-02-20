#ifndef SPRITE_COLLIDER
#define SPRITE_COLLIDER

#include <math.h>
#include <float.h>
#include "sprite.h"

extern bool add_sprites(SPRITE** sprites, int count);

extern void remove_sprites();

extern bool process_sprites(float dt);

#endif // SPRITE_COLLIDER
