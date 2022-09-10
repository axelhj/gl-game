#include "impl/Game/start.h"

#define TILE_WIDTH 1.0f
#define TILE_HEIGHT 1.0f
#define Z_POS 11.0f

static int grid[12 * 9] = {
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

static bool init(std::vector<Sprite*>& draw_sprites)
{
    for (int i = 1; i < 37; ++i) {
        draw_sprites.push_back(new Sprite("asset/crate.png"));
        draw_sprites[i]->set_size(0.999f, 0.999f);
        draw_sprites[i]->set_vel(0.0f, 0.0f, 0.0f);
        draw_sprites[i]->is_static = false;
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
    draw_sprites[36] = (Sprite*)new TextSprite();
    draw_sprites[36]->set_size(0.18f, 0.18f);
    draw_sprites[36]->set_vel(0.0f, 0.0f, 0.0f);
    draw_sprites[36]->set_pos(1.5f, -2.2f, Z_POS - 0.5f);
    draw_sprites[36]->is_static = true;
    return true;
}

Start::Start() :
    draw_sprites(), sprite_collider()
{
    draw_sprites.push_back(new Sprite("asset/pino.png"));
    init(draw_sprites);
    vector<Sprite*> pass_sprites(draw_sprites);
    sprite_collider.add_sprites(pass_sprites);
    draw_sprites[0]->set_pos(-1.495, 0.7, Z_POS);
    draw_sprites[0]->set_size(0.3, 0.3);
    draw_sprites[0]->is_static = false;
    int sprites_size = draw_sprites.size();
    for (int i = sprites_size; i < sprites_size + 12; ++i) {
        for (int j = 0; j < 9; ++j) {
            int offset = (i - sprites_size) + j * 12;
            Sprite* tile = new Sprite(grid[offset] ? "asset/wall.png" : "asset/ground.png");
            tile->set_pos((i - sprites_size) * TILE_WIDTH - 6.0f, j * TILE_HEIGHT - 4.5f, 23.0f);
            tile->size[0] = TILE_WIDTH;
            tile->size[1] = TILE_HEIGHT;
            tile->update_mat();
            draw_sprites.push_back(tile);
        }
    }
}

bool Start::update(int keys[], float dt, float t)
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

bool Start::draw()
{
    for (int i = 0; i < draw_sprites.size(); ++i) {
        if (i == 36) continue;
        draw_sprites[i]->update_mat();
        draw_sprites[i]->draw->draw_gl();
    }
    const char* full_string =
        "Det var en gång en liten fågel som hette Roger!";
    ((TextSprite*)(draw_sprites[36]))->draw_text(full_string, 17, 4);
    return true;
}

Start::~Start()
{
    sprite_collider.remove_sprites();
    draw_sprites.clear();
}
