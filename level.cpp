#include "level.h"

#define TILES_X 12
#define TILES_Y 9

#define TILE_WIDTH 1.0f
#define TILE_HEIGHT 1.0f

#define DRAW_SPRITES_COUNT 36

#define Z_POS 11.0f

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

static SPRITE* draw_sprites[DRAW_SPRITES_COUNT];

static bool init_crates()
{
    bool ok = true;
    for (int i = 1; i < DRAW_SPRITES_COUNT && ok; ++i) {
        ok = ok && create_sprite(&draw_sprites[i], "crate.png");
        if (ok) {
            set_sprite_size(draw_sprites[i], 0.999f, 0.999f);
            set_sprite_vel(draw_sprites[i], 0.0f, 0.0f, 0.0f);
            draw_sprites[i]->is_static = false;
        }
    }
    set_sprite_vel(draw_sprites[0], 0, 0, 0);
    set_sprite_pos(draw_sprites[1], 1.0f, 1.0f, Z_POS);
    set_sprite_pos(draw_sprites[2], 2.0f, 1.0f, Z_POS);
    set_sprite_pos(draw_sprites[3], 3.0f, 1.0f, Z_POS);
    set_sprite_pos(draw_sprites[4], 1.0f, 3.0f, Z_POS);
    set_sprite_pos(draw_sprites[5], 3.0f, 3.0f, Z_POS);
    set_sprite_pos(draw_sprites[6], 4.0f, 3.0f, Z_POS);
    set_sprite_pos(draw_sprites[7], -1.0f, -1.0f, Z_POS);
    set_sprite_pos(draw_sprites[8], -1.0f, -2.0f, Z_POS);
    set_sprite_pos(draw_sprites[9], -1.0f, -3.0f, Z_POS);
    for (int i = 1; i < 10; ++i) {
//        set_sprite_vel(draw_sprites[i], i > 5 ? 0.07 : -0.07, i > 5 ? 0.07 : -0.07, 0);
    }
    set_sprite_pos(draw_sprites[10], -5.5f, -3.0f, Z_POS);
    draw_sprites[10]->is_static = true;
    set_sprite_pos(draw_sprites[11], -5.5f, -2.0f, Z_POS);
    draw_sprites[11]->is_static = true;
    set_sprite_pos(draw_sprites[12], -5.5f, -1.0f, Z_POS);
    draw_sprites[12]->is_static = true;
    set_sprite_pos(draw_sprites[13], -5.5f, 0.0f, Z_POS);
    draw_sprites[13]->is_static = true;
    set_sprite_pos(draw_sprites[14], -5.5f, 1.0f, Z_POS);
    draw_sprites[14]->is_static = true;
    set_sprite_pos(draw_sprites[15], -5.5f, 2.0f, Z_POS);
    draw_sprites[15]->is_static = true;

    set_sprite_pos(draw_sprites[16], 1.5f, -3.0f, Z_POS);
    draw_sprites[16]->is_static = true;
    set_sprite_pos(draw_sprites[17], 1.5f, -2.0f, Z_POS);
    draw_sprites[17]->is_static = true;
    set_sprite_pos(draw_sprites[18], 1.5f, -1.0f, Z_POS);
    draw_sprites[18]->is_static = true;
    set_sprite_pos(draw_sprites[19], 1.5f, 0.0f, Z_POS);
    draw_sprites[19]->is_static = true;
    set_sprite_pos(draw_sprites[20], 1.5f, 1.0f, Z_POS);
    draw_sprites[20]->is_static = true;
    set_sprite_pos(draw_sprites[21], 1.5f, 2.0f, Z_POS);
    draw_sprites[21]->is_static = true;

    set_sprite_pos(draw_sprites[22], -4.5f, -3.0f, Z_POS);
    draw_sprites[22]->is_static = true;
    set_sprite_pos(draw_sprites[23], -3.5f, -3.0f, Z_POS);
    draw_sprites[23]->is_static = true;
    set_sprite_pos(draw_sprites[24], -2.5f, -3.0f, Z_POS);
    draw_sprites[24]->is_static = true;
    set_sprite_pos(draw_sprites[25], -1.5f, -3.0f, Z_POS);
    draw_sprites[25]->is_static = true;
    set_sprite_pos(draw_sprites[26], -0.5f, -3.0f, Z_POS);
    draw_sprites[26]->is_static = true;
    set_sprite_pos(draw_sprites[27], 0.5f, -3.0f, Z_POS);
    draw_sprites[27]->is_static = true;

    set_sprite_pos(draw_sprites[28], -5.5f, 3.0f, Z_POS);
    draw_sprites[28]->is_static = true;
    set_sprite_pos(draw_sprites[29], -4.5f, 3.0f, Z_POS);
    draw_sprites[29]->is_static = true;
    set_sprite_pos(draw_sprites[30], -3.5f, 3.0f, Z_POS);
    draw_sprites[30]->is_static = true;
    set_sprite_pos(draw_sprites[31], -2.5f, 3.0f, Z_POS);
    draw_sprites[31]->is_static = true;
    set_sprite_pos(draw_sprites[32], -1.5f, 3.0f, Z_POS);
    draw_sprites[32]->is_static = true;
    set_sprite_pos(draw_sprites[33], -0.5f, 3.0f, Z_POS);
    draw_sprites[33]->is_static = true;
    set_sprite_pos(draw_sprites[34], 0.5f, 3.0f, Z_POS);
    draw_sprites[34]->is_static = true;

    set_sprite_pos(draw_sprites[35], 1.5f, 3.0f, Z_POS);
    draw_sprites[35]->is_static = true;
    return ok;
}

bool init_level()
{
    bool ok = create_sprite(&draw_sprites[0], "game-hero.png");
    ok = ok && init_crates();
    ok = ok && add_sprites(draw_sprites, DRAW_SPRITES_COUNT);
    set_sprite_pos(draw_sprites[0], -1.495, 0.7, Z_POS);
    set_sprite_size(draw_sprites[0], 0.3, 0.3);
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
//    int a = keys[4];
//    int b = keys[5];
    float rate = 1.2;
    float* vel = draw_sprites[0]->vel;
    vel[0] = 0;
    vel[1] = 0;
    if (d) {
        vel[1] -= rate;
    } else if (u) {
        vel[1] += rate;
    }
    if (l) {
        vel[0] -= rate;
    } else if (r) {
        vel[0] += rate;
    }
    process_sprites(dt);
    return true;
}

bool draw_level()
{
    for (int i = 0; i < TILES_X * TILES_Y; ++i) {
        draw_gl(tiles[i]->draw_entity);
    }
    for (int i = 0; i < DRAW_SPRITES_COUNT; ++i) {
        update_model_mat(draw_sprites[i]);
        draw_gl(draw_sprites[i]->draw_entity);
    }
    return true;
}

bool destroy_level()
{
    remove_sprites();
    for (int i = 0; i < TILES_X * TILES_Y; ++i) {
        destroy_sprite(tiles[i]);
    }
    for (int i = 0; i < DRAW_SPRITES_COUNT; ++i) {
        destroy_sprite(draw_sprites[i]);
    }
    return true;
}
