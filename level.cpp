#include "level.h"

#define TILE_WIDTH 1.0f
#define TILE_HEIGHT 1.0f
#define Z_POS 11.0f

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

static bool init(Sprite** draw_sprites)
{
    bool ok = true;
    for (int i = 1; i < DRAW_SPRITES_COUNT && ok; ++i) {
        draw_sprites[i] = new Sprite("crate.png");
        if (ok) {
            draw_sprites[i]->set_size(0.999f, 0.999f);
            draw_sprites[i]->set_vel(0.0f, 0.0f, 0.0f);
            draw_sprites[i]->is_static = false;
        }
    }
    draw_sprites[0]->set_vel(0, 0, 0);
    draw_sprites[1]->set_pos(1.0f, 1.0f, Z_POS);
    draw_sprites[2]->set_pos(2.0f, 1.0f, Z_POS);
    draw_sprites[3]->set_pos(3.0f, 1.0f, Z_POS);
    draw_sprites[4]->set_pos(1.0f, 3.0f, Z_POS);
    draw_sprites[5]->set_pos(3.0f, 3.0f, Z_POS);
    draw_sprites[6]->set_pos(4.0f, 3.0f, Z_POS);
    draw_sprites[7]->set_pos(-1.0f, -1.0f, Z_POS);
    draw_sprites[8]->set_pos(-1.0f, -2.0f, Z_POS);
    draw_sprites[9]->set_pos(-1.0f, -3.0f, Z_POS);
    for (int i = 1; i < 10; ++i) {
//        draw_sprites[i]->set_vel(i > 5 ? 0.07 : -0.07, i > 5 ? 0.07 : -0.07, 0);
    }
    draw_sprites[10]->set_pos(-5.5f, -3.0f, Z_POS);
    draw_sprites[10]->is_static = true;
    draw_sprites[11]->set_pos(-5.5f, -2.0f, Z_POS);
    draw_sprites[11]->is_static = true;
    draw_sprites[12]->set_pos(-5.5f, -1.0f, Z_POS);
    draw_sprites[12]->is_static = true;
    draw_sprites[13]->set_pos(-5.5f, 0.0f, Z_POS);
    draw_sprites[13]->is_static = true;
    draw_sprites[14]->set_pos(-5.5f, 1.0f, Z_POS);
    draw_sprites[14]->is_static = true;
    draw_sprites[15]->set_pos(-5.5f, 2.0f, Z_POS);
    draw_sprites[15]->is_static = true;

    draw_sprites[16]->set_pos(1.5f, -3.0f, Z_POS);
    draw_sprites[16]->is_static = true;
    draw_sprites[17]->set_pos(1.5f, -2.0f, Z_POS);
    draw_sprites[17]->is_static = true;
    draw_sprites[18]->set_pos(1.5f, -1.0f, Z_POS);
    draw_sprites[18]->is_static = true;
    draw_sprites[19]->set_pos(1.5f, 0.0f, Z_POS);
    draw_sprites[19]->is_static = true;
    draw_sprites[20]->set_pos(1.5f, 1.0f, Z_POS);
    draw_sprites[20]->is_static = true;
    draw_sprites[21]->set_pos(1.5f, 2.0f, Z_POS);
    draw_sprites[21]->is_static = true;

    draw_sprites[22]->set_pos(-4.5f, -3.0f, Z_POS);
    draw_sprites[22]->is_static = true;
    draw_sprites[23]->set_pos(-3.5f, -3.0f, Z_POS);
    draw_sprites[23]->is_static = true;
    draw_sprites[24]->set_pos(-2.5f, -3.0f, Z_POS);
    draw_sprites[24]->is_static = true;
    draw_sprites[25]->set_pos(-1.5f, -3.0f, Z_POS);
    draw_sprites[25]->is_static = true;
    draw_sprites[26]->set_pos(-0.5f, -3.0f, Z_POS);
    draw_sprites[26]->is_static = true;
    draw_sprites[27]->set_pos(0.5f, -3.0f, Z_POS);
    draw_sprites[27]->is_static = true;

    draw_sprites[28]->set_pos(-5.5f, 3.0f, Z_POS);
    draw_sprites[28]->is_static = true;
    draw_sprites[29]->set_pos(-4.5f, 3.0f, Z_POS);
    draw_sprites[29]->is_static = true;
    draw_sprites[30]->set_pos(-3.5f, 3.0f, Z_POS);
    draw_sprites[30]->is_static = true;
    draw_sprites[31]->set_pos(-2.5f, 3.0f, Z_POS);
    draw_sprites[31]->is_static = true;
    draw_sprites[32]->set_pos(-1.5f, 3.0f, Z_POS);
    draw_sprites[32]->is_static = true;
    draw_sprites[33]->set_pos(-0.5f, 3.0f, Z_POS);
    draw_sprites[33]->is_static = true;
    draw_sprites[34]->set_pos(0.5f, 3.0f, Z_POS);
    draw_sprites[34]->is_static = true;

    draw_sprites[35]->set_pos(1.5f, 3.0f, Z_POS);
    draw_sprites[35]->is_static = true;
    return ok;
}

Level::Level()
{
    draw_sprites[0] = new Sprite("game-hero.png");
    init(draw_sprites);
    add_sprites(draw_sprites, DRAW_SPRITES_COUNT);
    draw_sprites[0]->set_pos(-1.495, 0.7, Z_POS);
    draw_sprites[0]->set_size(0.3, 0.3);
    for (int i = 0; i < TILES_X; ++i) {
        for (int j = 0; j < TILES_Y; ++j) {
            int offset= i + TILES_X * j;
            if (grid[offset]) {
                tiles[offset] = new Sprite("wall.png");
            } else {
                tiles[offset] = new Sprite("ground.png");
            }
            Sprite* tile = tiles[i + TILES_X * j];
            tile->set_pos(i * TILE_WIDTH - 6.0f, j * TILE_HEIGHT - 4.5f, 12.0f);
            tile->size[0] = TILE_WIDTH;
            tile->size[1] = TILE_HEIGHT;
            tile->update_mat();
        }
    }
}

bool Level::update(int keys[], float dt, float t)
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

bool Level::draw()
{
    for (int i = 0; i < TILES_X * TILES_Y; ++i) {
        tiles[i]->draw->draw_gl();
    }
    for (int i = 0; i < DRAW_SPRITES_COUNT; ++i) {
        draw_sprites[i]->update_mat();
        draw_sprites[i]->draw->draw_gl();
    }
    return true;
}

Level::~Level()
{
    remove_sprites();
    for (int i = 0; i < TILES_X * TILES_Y; ++i) {
        delete tiles[i];
    }
    for (int i = 0; i < DRAW_SPRITES_COUNT; ++i) {
        delete draw_sprites[i];
    }
}
