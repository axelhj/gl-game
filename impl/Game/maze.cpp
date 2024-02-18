#include "impl/Game/maze.h"

#include <cstdio>
#include <math.h>

#include "impl/Engine/text_sprite.h"

#define TILE_WIDTH 0.999f
#define TILE_HEIGHT 0.999f

#define Z_POS 11.0f

static bool init(Sprite** draw_sprites)
{
    draw_sprites[1] = new Sprite("asset/crate.png");
    draw_sprites[1]->set_size(0.999f, 0.999f);
    draw_sprites[1]->set_vel(0.0f, 0.0f, 0.0f);
    draw_sprites[1]->set_pos(100.0f, 100.0f, Z_POS);
    draw_sprites[1]->is_static = true;
    for (int i = 1; i < DRAW_SPRITES_COUNT; ++i) {
        draw_sprites[i] = new Sprite(draw_sprites[1]->draw->texture_id);
        draw_sprites[i]->set_size(0.999f, 0.999f);
        draw_sprites[i]->set_vel(0.0f, 0.0f, 0.0f);
        draw_sprites[i]->set_pos(1.0f, 1.0f, Z_POS);
        draw_sprites[i]->is_static = false;
    }
//    draw_sprites[36] = (Sprite*)new TextSprite();
//    draw_sprites[36]->set_size(0.18f, 0.18f);
//    draw_sprites[36]->set_vel(0.0f, 1.0f, 0.0f);
//    draw_sprites[36]->set_pos(1.5f, -2.2f, Z_POS - 0.5f);
//    draw_sprites[37] = new Sprite("asset/white.png");
//    draw_sprites[37]->set_size(0.18f, 0.18f);
//    draw_sprites[37]->set_vel(0.0f, -1.0f, 0.0f);
//    draw_sprites[37]->set_pos(-1.5f, 2.2f, Z_POS - 0.5f);
//    draw_sprites[37]->is_static = true;
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
        draw_sprites[i]->set_vel(i > 5 ? 0.07 : -0.07, i > 5 ? 0.07 : -0.07, 0);
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
    return true;
}

Maze::Maze()
{
    draw_sprites[0] = new Sprite("asset/pino.png");
    init(draw_sprites);
    vector<Sprite*> pass_sprites(
        draw_sprites,
        draw_sprites + 1
    );
    sprite_collider.add_sprites(pass_sprites);
    draw_sprites[0]->set_pos(-1.795, 0.7, Z_POS);
    draw_sprites[0]->set_size(.7, 0.7);
    draw_sprites[0]->set_vel(0, 0, 0);
    draw_sprites[0]->is_static = false;
    int path_length = 0;
    int* path = NULL;
    int start_index = 14 - 1;
    int end_index = 65 - 1;
    int blocked[TILES_X * TILES_Y] = {};
    int blocked_count = 0;
    find_path_in_grid(
        &path_length,
        &path,
        blocked_count,
        blocked,
        TILES_X,
        TILES_Y,
        start_index,
        end_index
    );
//    for (int i = 0; i < path_length; ++i) {
//        int path_step = path[i];
//        int x = (int)fmod(path_step, TILES_X);
//        int y = (int)(path_step / TILES_X);
//        blocked[blocked_count++] = i;
//        printf("%d, %d is %s\n", x, y, "not blocked");
//    }
    for (int i = 0; i < TILES_X; ++i) {
        for (int j = 0; j < TILES_Y; ++j) {
            int offset = i + TILES_X * j;
            bool is_blocked = true;
            for (int k = 0; k < path_length; ++k) {
                int path_step = path[k];
                if (path_step == offset) {
                    is_blocked = false;
                    int x = (int)fmod(path_step, TILES_X);
                    int y = (int)(path_step / TILES_X);
                    printf("%d, %d is %s\n", x, y, "unblocked is true");
                }
            }
            if (is_blocked) {
                tiles[offset] = new Sprite("asset/wall.png");
                vector<Sprite*> pass_sprites(tiles + offset, tiles + offset + 1);
                sprite_collider.add_sprites(pass_sprites);
            } else {
                tiles[offset] = new Sprite("asset/ground.png");
            }
            Sprite* tile = tiles[offset];
            tile->is_static = true;
            tile->set_pos(i * TILE_WIDTH - 6.0f, j * TILE_HEIGHT - 4.5f, Z_POS + 0.0001f);
            tile->size[0] = TILE_WIDTH;
            tile->size[1] = TILE_HEIGHT;
            tile->set_vel(0.0f, 0.0f, 0.0f);
            tile->update_mat();
        }
    }
}

bool Maze::update(int keys[], float dt, float t)
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
    sprite_collider.process_sprites(dt);
    return true;
}

bool Maze::draw()
{
    for (int i = 0; i < TILES_X * TILES_Y; ++i) {
        tiles[i]->update_mat();
        tiles[i]->draw->draw_gl();
    }
    for (int i = 0; i < DRAW_SPRITES_COUNT - 1; ++i) {
        draw_sprites[i]->update_mat();
        draw_sprites[i]->draw->draw_gl();
    }
    draw_sprites[36]->update_mat();
    const char* full_string =
        "Det var en gång en liten fågel som hette Roger!";
    ((TextSprite*)(draw_sprites[36]))->draw_text(full_string, 4, 17);
    draw_sprites[37]->update_mat();
    draw_sprites[37]->draw->draw_gl();
    return true;
}

Maze::~Maze()
{
    sprite_collider.remove_sprites();
    for (int i = 0; i < TILES_X * TILES_Y; ++i) {
        delete tiles[i];
    }
    for (int i = 0; i < DRAW_SPRITES_COUNT; ++i) {
        delete draw_sprites[i];
    }
}
