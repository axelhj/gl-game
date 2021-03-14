#include "sprite_collider.h"

#define SPRITES_MAX 25

#define NONE 0
#define RIGHT 1
#define LEFT 2
#define TOP 3
#define BOTTOM 4

static int sprites_count = 0;

static SPRITE** sprites = NULL;

bool add_sprites(SPRITE** add_sprites, int count)
{
    int new_count = count + sprites_count;
    if (new_count > SPRITES_MAX) {
        return false;
    }
    if (sprites_count == 0) {
        sprites = (SPRITE**)malloc(sizeof(SPRITE**) * SPRITES_MAX);
        if (sprites == NULL) {
            return false;
        }
    }
    for (int i = sprites_count; i < new_count; ++i) {
        sprites[i] = add_sprites[i];
    }
    sprites_count = new_count;
    return true;
}

void remove_sprites()
{
    if (sprites_count != 0) {
        free(sprites);
        sprites = NULL;
        sprites_count = 0;
    }
}

const char* coll_mode_labels [5] = {
    "",
    "a right", // 1
    "a left", // 2
    "a top", // 3
    "a bottom" // 4
};

static float normals[12] = {
    -1.0f, 0.0f, 0.0f, // right
    1.0f, 0.0f, 0.0f, // left
    0.0f, -1.0f, 0.0f, // top
    0.0f, 1.0f, 0.0f // bottom
};

typedef struct collision_values {
    int mode_a;
    int mode_b;
    float time;
    SPRITE* other;
} COLLISION_VALUES;

static bool is_colliding_x(
    SPRITE* a,
    SPRITE* b,
    float time
)
{
    float top_a = a->pos[1] + a->vel[1] * time + a->size[1];
    float top_b = b->pos[1] + b->vel[1] * time + b->size[1];
    float bottom_a = a->pos[1] + a->vel[1] * time;
    float bottom_b = b->pos[1] + b->vel[1] * time;
    return (
        (top_a > bottom_b &&
        top_b > bottom_a) &&
        (bottom_a < top_b &&
        bottom_b < top_a)
    );
}

static bool is_colliding_y(
    SPRITE* a,
    SPRITE* b,
    float time
)
{
    float left_a = a->pos[0] + a->vel[0] * time;
    float left_b = b->pos[0] + b->vel[0] * time;
    float right_a = a->pos[0] + a->vel[0] * time + a->size[0];
    float right_b = b->pos[0] + b->vel[0] * time + b->size[0];
    return (
        (left_a < right_b &&
        left_b < right_a) &&
        (right_a > left_b &&
        right_b > left_a)
    );
}

static COLLISION_VALUES intersection_time(SPRITE* a, SPRITE* b)
{
    float left_a = a->pos[0];
    float left_b = b->pos[0];
    float right_a = a->pos[0] + a->size[0];
    float right_b = b->pos[0] + b->size[0];
    float top_a = a->pos[1] + a->size[1];
    float top_b = b->pos[1] + b->size[1];
    float bottom_a = a->pos[1];
    float bottom_b = b->pos[1];

    float a_vel_x = a->vel[0];
    float a_vel_y = a->vel[1];
    float b_vel_x = b->vel[0];
    float b_vel_y = b->vel[1];

    float time = 0;
    COLLISION_VALUES collision;
    collision.time = FLT_MAX;
    collision.mode_a = NONE;
    collision.mode_b = NONE;
    if (a_vel_x > 0 && right_a < left_b) {
        time = (left_b - right_a) / (a_vel_x - b_vel_x);
        if (time >= 0 && time < collision.time && is_colliding_x(a, b, time)) {
            collision.time = time;
            collision.mode_a = RIGHT;
            collision.mode_b = LEFT;
            collision.other = b;
        }
    }
    if (a_vel_x < 0 && left_a > right_b) {
        time = (right_b - left_a) / (a_vel_x - b_vel_x);
        if (time >= 0 && time < collision.time && is_colliding_x(a, b, time)) {
            collision.time = time;
            collision.mode_a = LEFT;
            collision.mode_b = RIGHT;
            collision.other = b;
        }
    }
    if (a_vel_y > 0 && top_a < bottom_b) {
        time = (bottom_b - top_a) / (a_vel_y - b_vel_y);
        if (time >= 0 && time < collision.time && is_colliding_y(a, b, time)) {
            collision.time = time;
            collision.mode_a = TOP;
            collision.mode_b = BOTTOM;
            collision.other = b;
        }
    }
    if (a_vel_y < 0 && bottom_a > top_b) {
        time = (top_b - bottom_a) / (a_vel_y - b_vel_y);
        if (time >= 0 && time < collision.time && is_colliding_y(a, b, time)) {
            collision.time = time;
            collision.mode_a = BOTTOM;
            collision.mode_b = TOP;
            collision.other = b;
        }
    }
    return collision;
}

static COLLISION_VALUES find_collision_time(SPRITE* a, float dt)
{
    COLLISION_VALUES found_collision;
    found_collision.mode_a = NONE;
    found_collision.mode_b = NONE;
    found_collision.time = FLT_MAX;
    for (int i = 0; i < sprites_count; ++i) {
        if (sprites[i] != a) {
            COLLISION_VALUES collision = intersection_time(a, sprites[i]);
            if (collision.time >= 0 && collision.time < found_collision.time) {
                found_collision = collision;
            }
        }
    }
    return found_collision;
}

bool process_sprites(float dt)
{
    float processed_time = 0.0f;
    SPRITE* first_collision_sprite = NULL;
    COLLISION_VALUES first_collision;
    first_collision.mode_a = NONE;
    first_collision.mode_b = NONE;
    first_collision.time = 0.0f;
    while (processed_time < dt) {
        first_collision.mode_a = NONE;
        for (int i = 0; i < sprites_count; ++i) {
            COLLISION_VALUES collision = find_collision_time(sprites[i], dt);
            if (collision.time >= processed_time && processed_time + collision.time < dt) {
                first_collision = collision;
                first_collision_sprite = sprites[i];
            }
        }
        if (first_collision.mode_a != NONE) {
            for (int i = 0; i < sprites_count; ++i) {
                sprites[i]->pos[0] += first_collision_sprite->vel[0] * first_collision.time;
                sprites[i]->pos[1] += first_collision_sprite->vel[1] * first_collision.time;
                sprites[i]->pos[2] += sprites[i]->vel[2] * first_collision.time;
            }
            processed_time += first_collision.time;
            first_collision.time = 0.0f;
            float vel[3];
            float orig_vel[3];
            orig_vel[0] = first_collision_sprite->vel[0];
            orig_vel[1] = first_collision_sprite->vel[1];
            orig_vel[2] = first_collision_sprite->vel[2];
            vec_3_reflect(vel, sprites[0]->vel, normals + (first_collision.mode_a - 1) * 3);
            first_collision_sprite->vel[0] = vel[0] + first_collision.other->vel[0];
            first_collision_sprite->vel[1] = vel[1] + first_collision.other->vel[1];
            first_collision_sprite->vel[2] = vel[2] + first_collision.other->vel[2];
            vec_3_reflect(vel, first_collision.other->vel, normals + (first_collision.mode_b - 1) * 3);
            first_collision.other->vel[0] = vel[0] + orig_vel[0];
            first_collision.other->vel[1] = vel[1] + orig_vel[1];
            first_collision.other->vel[2] = vel[2] + orig_vel[2];
        } else {
            for (int i = 0; i < sprites_count; ++i) {
                sprites[i]->pos[0] += sprites[i]->vel[0] * (dt - processed_time);
                sprites[i]->pos[1] += sprites[i]->vel[1] * (dt - processed_time);
                sprites[i]->pos[2] += sprites[i]->vel[2] * (dt - processed_time);
            }
            processed_time = dt;
        }
    }
    return true;
}
