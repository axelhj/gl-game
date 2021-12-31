#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>
#include "draw.h"
#include "mat4.h"

typedef struct sprite {
    float pos[3];
    float vel[3];
    float size[2];
    Draw* draw;
    bool is_static;
} SPRITE;

extern bool create_sprite(SPRITE** sprite, const char* textureName);

extern bool destroy_sprite(SPRITE* sprite);

extern void set_sprite_pos(SPRITE* sprite, float x, float y, float z);

extern void set_sprite_vel(SPRITE* sprite, float x, float y, float z);

extern void set_sprite_size(SPRITE* sprite, float w, float h);

extern void update_model_mat(SPRITE* sprite);

#endif /* SPRITE_H */
