#include "level.h"

static SPRITE* draw_sprite;

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
    bool ok = create_sprite(&draw_sprite, "game-hero.png");
    set_sprite_size(draw_sprite, 0.3, 0.3);
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
    set_sprite_pos(draw_sprite, pos[0], pos[1], pos[2]);
    return true;
}

bool draw_level()
{
    update_model_mat(draw_sprite);
    drawGl(draw_sprite->draw_entity);
    for (int i = 0; i < TILES_X * TILES_Y; ++i) {
        drawGl(tiles[i]->draw_entity);
    }
    return true;
}

bool destroy_level()
{
    destroy_sprite(draw_sprite);
    for (int i = 0; i < TILES_X * TILES_Y; ++i) {
        destroy_sprite(tiles[i]);
    }
    return true;
}
