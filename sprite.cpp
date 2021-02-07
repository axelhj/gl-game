#include "sprite.h"

bool create_sprite(SPRITE** sprite, const char* textureName)
{
    *sprite = (SPRITE*)malloc(sizeof(SPRITE));
    bool success = *sprite != NULL;
    (*sprite)->draw_entity = (DRAW_ENTITY*)malloc (sizeof(DRAW_ENTITY));
    success = success && (*sprite)->draw_entity != NULL;
    setSquareVertexData((*sprite)->draw_entity);
    success = success && loadGl((*sprite)->draw_entity);
    success = success && loadGlTexture((*sprite)->draw_entity, textureName);
    return success;
}

bool destroy_sprite(SPRITE* sprite)
{
    // TODO: Implement OGL resource cleanup.
    free(sprite->draw_entity);
    free(sprite);
    return true;
}

void set_sprite_pos(SPRITE* sprite, float x, float y)
{
    sprite->pos[0] = x;
    sprite->pos[1] = y;
}

void set_sprite_size(SPRITE* sprite, float w, float h)
{
    sprite->size[0] = w;
    sprite->size[1] = h;
}

void update_model_mat(SPRITE* sprite)
{
    GLfloat* modelMat = sprite->draw_entity->modelMat;
    float* pos = sprite->pos;
    float* size = sprite->size;
    GLfloat intermediate[16];
    GLfloat modelMatCopy[16];
    mat_scale(modelMatCopy, size[0], size[1], 1);
    mat_translation(intermediate, pos[0], pos[1], 0);
    mat_multiplicate(modelMatCopy, intermediate, modelMat);
}
