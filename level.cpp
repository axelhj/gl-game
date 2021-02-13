#include "level.h"

static DRAW_ENTITY* drawEntity;

static float pos[3] = {
    -0.495, 0.495, 0.198
};

#define TILES_X 12
#define TILES_Y 9

#define TILE_WIDTH 1.0f
#define TILE_HEIGHT 1.0f

static SPRITE* tiles[TILES_X * TILES_Y];

static int grid[TILES_X * TILES_Y] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
    1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

bool init_level()
{
    drawEntity = (DRAW_ENTITY*)malloc(sizeof(DRAW_ENTITY));
    setSquareVertexData(drawEntity);
    bool ok = loadGl(drawEntity);
    ok = ok && loadGlTexture(drawEntity, "game-hero.png");
    for (int i = 0; i < TILES_X; ++i) {
        for (int j = 0; j < TILES_Y && ok; ++j) {
            int offset= i + TILES_X * j;
            if (grid[offset]) {
                ok = create_sprite(tiles + offset, "wall.png");
            } else {
                ok = create_sprite(tiles + offset, "ground.png");
            }
            SPRITE* tile = tiles[i + TILES_X * j];
            set_sprite_pos(tile, i * TILE_WIDTH - 6.0f, j * TILE_HEIGHT - 4.5f, 12.0f);
            tile->size[0] = TILE_WIDTH;
            tile->size[1] = TILE_HEIGHT;
            update_model_mat(tile);
        }
    }
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
    drawGl(drawEntity);
    for (int i = 0; i < TILES_X * TILES_Y; ++i) {
        drawGl(tiles[i]->draw_entity);
    }
    return true;
}

bool destroy_level()
{
    free(drawEntity);
    for (int i = 0; i < TILES_X * TILES_Y; ++i) {
        destroy_sprite(tiles[i]);
    }
    return true;
}
