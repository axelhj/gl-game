#include "level.h"

static SPRITE* entities[5] = { 0, 0, 0, 0, 0 };

static DRAW_ENTITY* drawEntity;

static float pos[3] = {
    -0.495, 0.495, 0.198
};

bool init_level()
{
    bool ok = create_sprite(entities + 0, "game-hero.png");
    drawEntity = (*entities)->draw_entity;
    ok = ok && create_sprite(entities + 1, "ground.png");
    mat_translation((*(entities + 0))->draw_entity->viewMat, 0.35f, -0.37f, 1.0f);
    mat_translation((*(entities + 1))->draw_entity->modelMat, -0.495, 0.495, 0.198);
    GLfloat* intermediate = (float*)malloc(sizeof(float)*16);
    mat_rot_x(intermediate, 3.1415f / 2.0f);
    GLfloat* modelMatCopy = mat_copy((*(entities + 1))->draw_entity->modelMat);
    mat_multiplicate(modelMatCopy, intermediate, (*(entities + 1))->draw_entity->modelMat);
    mat_destroy(modelMatCopy);
    mat_destroy(intermediate);
    return ok;
}

bool update_level(int keys[], float dt, float t)
{
    int l = keys[0];
    int r = keys[1];
    int u = keys[2];
    int d = keys[3];
    int a = keys[4];
    int b = keys[5];
    float rate = 3.0 * 0.0165;
    if (d) {
        pos[1] -= rate;
    } else if (u) {
        pos[1] += rate;
    }
    if (l) {
        pos[0] -= rate;
    } else if (r) {
        pos[0] += rate;
    }
    if (a) {
        pos[2] -= rate;
    } else if (b) {
        pos[2] += rate;
    }
    mat_scale(drawEntity->modelMat, 0.3, 0.3, 0.3);
    GLfloat* intermediate = (float*)malloc(sizeof(float)*16);
    // Pass 0
    mat_rot_x(intermediate, 3.1415);
    GLfloat* modelMatCopy = mat_copy(drawEntity->modelMat);
    mat_multiplicate(modelMatCopy, intermediate, drawEntity->modelMat);
    // Pass 1
    mat_rot_y(intermediate, 3.1415f / 4.0f);
    modelMatCopy = mat_copy(drawEntity->modelMat);
    mat_multiplicate(modelMatCopy, intermediate, drawEntity->modelMat);
    // Pass 2
    mat_translation(intermediate, pos[0], pos[1], pos[2]);
    mat_set_to(modelMatCopy, drawEntity->modelMat);
    mat_multiplicate(modelMatCopy, intermediate, drawEntity->modelMat);

    mat_destroy(modelMatCopy);
    mat_destroy(intermediate);
    return true;
}

bool draw_level()
{
    drawGl((*(entities + 0))->draw_entity);
    drawGl((*(entities + 1))->draw_entity);
    return true;
}

bool destroy_level()
{
    // TODO
    return true;
}
