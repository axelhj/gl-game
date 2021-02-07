#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>
#include "draw.h"
#include "mat4.h"

typedef struct sprite {
    float pos[];
    float size[];
    DRAW_ENTITY* draw_entity;
} SPRITE;

extern bool create_sprite(SPRITE** sprite, const char* textureName);

extern bool destroy_sprite(SPRITE* sprite);

extern void set_sprite_pos(SPRITE* sprite, float x, float y);

extern void set_sprite_size(SPRITE* sprite, float w, float h);

extern void update_model_mat(SPRITE* sprite);

#endif /* SPRITE_H */
