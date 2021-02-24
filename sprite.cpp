#include "sprite.h"

bool create_sprite(SPRITE** sprite, const char* texture_name)
{
    *sprite = (SPRITE*)malloc(sizeof(SPRITE));
    bool success = *sprite != NULL;
    (*sprite)->draw_entity = (DRAW_ENTITY*)malloc(sizeof(DRAW_ENTITY));
    success = success && (*sprite)->draw_entity != NULL;
    set_square_vertex_data((*sprite)->draw_entity);
    success = success && load_gl((*sprite)->draw_entity);
    success = success && load_gl_texture((*sprite)->draw_entity, texture_name);
    return success;
}

bool destroy_sprite(SPRITE* sprite)
{
    bool success = unload_gl(sprite->draw_entity) || false;
    success = success && unload_gl_texture(sprite->draw_entity);
    free(sprite->draw_entity);
    free(sprite);
    return true;
}

void set_sprite_pos(SPRITE* sprite, float x, float y, float z)
{
    sprite->pos[0] = x;
    sprite->pos[1] = y;
    sprite->pos[2] = z;
}

void set_sprite_vel(SPRITE* sprite, float x, float y, float z)
{
    sprite->vel[0] = x;
    sprite->vel[1] = y;
    sprite->vel[2] = z;
}

void set_sprite_size(SPRITE* sprite, float w, float h)
{
    sprite->size[0] = w;
    sprite->size[1] = h;
}

void update_model_mat(SPRITE* sprite)
{
    GLfloat* model_mat = sprite->draw_entity->model_mat;
    float* pos = sprite->pos;
    float* size = sprite->size;
    GLfloat intermediate[16];
    GLfloat model_mat_copy[16];
    mat_scale(model_mat_copy, size[0], size[1], 1);
    mat_translation(intermediate, pos[0], pos[1], pos[2]);
    mat_multiplicate(model_mat_copy, intermediate, model_mat);
}
