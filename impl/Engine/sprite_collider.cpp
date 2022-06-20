#include "impl/Engine/sprite_collider.h"

#define SPRITES_MAX 1000
#define COLLISIONS_MAX 20

#define NONE 0
#define RIGHT 1
#define LEFT 2
#define TOP 3
#define BOTTOM 4

SpriteCollider::SpriteCollider() :
    sprites(NULL), sprite_count(0)
{
}

bool SpriteCollider::add_sprites(Sprite** add_sprites, int count)
{
    int new_count = count + sprite_count;
    if (new_count > SPRITES_MAX) {
        return false;
    }
    if (sprite_count == 0) {
        sprites = new Sprite*[SPRITES_MAX];
        for (int i = 0; i < SPRITES_MAX; ++i) {
            sprites[i] = new Sprite();
        }
    }
    for (int i = sprite_count, j = 0; i < new_count; ++i, ++j) {
        sprites[i] = add_sprites[j];
    }
    sprite_count = new_count;
    return true;
}

void SpriteCollider::remove_sprites()
{
    if (sprite_count != 0) {
        delete[] sprites;
        sprites = NULL;
        sprite_count = 0;
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
    Sprite* sprite;
    Sprite* other_sprite;
} COLLISION_VALUES;

static bool is_colliding_x(
    Sprite* a,
    Sprite* b,
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
    Sprite* a,
    Sprite* b,
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

static COLLISION_VALUES intersection_time(Sprite* a, Sprite* b)
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
    collision.sprite = a;
    collision.other_sprite = b;
    if (a_vel_x > 0 && right_a < left_b) {
        time = (left_b - right_a) / (a_vel_x - b_vel_x);
        if (time >= 0 && time < collision.time && is_colliding_x(a, b, time)) {
            collision.time = time;
            collision.mode_a = RIGHT;
            collision.mode_b = LEFT;
        }
    }
    if (a_vel_x < 0 && left_a > right_b) {
        time = (right_b - left_a) / (a_vel_x - b_vel_x);
        if (time >= 0 && time < collision.time && is_colliding_x(a, b, time)) {
            collision.time = time;
            collision.mode_a = LEFT;
            collision.mode_b = RIGHT;
        }
    }
    if (a_vel_y > 0 && top_a < bottom_b) {
        time = (bottom_b - top_a) / (a_vel_y - b_vel_y);
        if (time >= 0 && time < collision.time && is_colliding_y(a, b, time)) {
            collision.time = time;
            collision.mode_a = TOP;
            collision.mode_b = BOTTOM;
        }
    }
    if (a_vel_y < 0 && bottom_a > top_b) {
        time = (top_b - bottom_a) / (a_vel_y - b_vel_y);
        if (time >= 0 && time < collision.time && is_colliding_y(a, b, time)) {
            collision.time = time;
            collision.mode_a = BOTTOM;
            collision.mode_b = TOP;
        }
    }
    return collision;
}

static int find_collision_time(
    COLLISION_VALUES **collisions,
    Sprite** sprites,
    int sprite_count,
    int collisions_count,
    int max_collisions,
    Sprite* a,
    float time
)
{
    int count = collisions_count;
    for (int i = 0; i < sprite_count; ++i) {
        if (sprites[i] == a) {
            continue;
        }
        COLLISION_VALUES collision = intersection_time(a, sprites[i]);
        if (
            count != 0 && collision.time >= 0 &&
            collision.time != FLT_MAX && collision.time == (*collisions)[0].time &&
            collision.time <= time
        ) {
            if (count >= max_collisions) {
                printf("ALERT: Maximum simultaneous collisions exceeded %d\n", max_collisions);
            } else {
                (*collisions)[count] = collision;
                ++count;
            }
        } else if (
            collision.time >= 0 &&
            collision.time != FLT_MAX && collision.time <= time
         ){
             if (count == 0) {
                (*collisions)[0] = collision;
                count = 1;
            } else if (collision.time < (*collisions)[0].time) {
                (*collisions)[0] = collision;
                count = 1;
            }
        }
    }
    return count;
}

bool SpriteCollider::process_sprites(float dt)
{
    static Sprite* resolved[COLLISIONS_MAX] = {};
    static COLLISION_VALUES candidate_collision_set[COLLISIONS_MAX] = {};
    static COLLISION_VALUES collision_set[COLLISIONS_MAX] = {};
    static int candidate_collision_count = 0;
    static int collision_count = 0;
    float processed_time = 0.0f;
    while (processed_time < dt) {
        for (int i = 0; i < sprite_count; ++i) {
            COLLISION_VALUES* candidate_collision_set_ptr = &(*candidate_collision_set);
            candidate_collision_count = find_collision_time(
                &candidate_collision_set_ptr,
                sprites,
                sprite_count,
                candidate_collision_count,
                COLLISIONS_MAX,
                sprites[i],
                dt - processed_time
            );
            if (
                candidate_collision_count != 0 && candidate_collision_set[0].time >= 0 &&
                candidate_collision_set[0].time < dt - processed_time
            ) {
                collision_count = candidate_collision_count;
                for (int j = 0; j < collision_count; ++j) {
                    collision_set[j] = candidate_collision_set[j];
                }
            }
        }
        for (int i = 0; i < COLLISIONS_MAX && resolved[i] != NULL; ++i) {
            resolved[i] = NULL;
        }
        if (collision_count != 0) {
            for (int j = 0; j < sprite_count; ++j) {
                sprites[j]->pos[0] += sprites[j]->vel[0] * fmaxf(0.0f, collision_set[0].time - 0.0000001f);
                sprites[j]->pos[1] += sprites[j]->vel[1] * fmaxf(0.0f, collision_set[0].time - 0.0000001f);
                sprites[j]->pos[2] += sprites[j]->vel[2] * fmaxf(0.0f, collision_set[0].time - 0.0000001f);
            }
        }
        for (int i = 0; i < collision_count; ++i) {
            float vel[3];
            float orig_vel[3];
            orig_vel[0] = collision_set[i].sprite->vel[0];
            orig_vel[1] = collision_set[i].sprite->vel[1];
            orig_vel[2] = collision_set[i].sprite->vel[2];
            float vel_a_momentum = vec_3_length(collision_set[i].sprite->vel);
            float vel_b_momentum = vec_3_length(collision_set[i].other_sprite->vel);
            bool skip = false;
            if (!collision_set[i].sprite->is_static) {
                for (int j = 0; j < COLLISIONS_MAX && resolved[j] != NULL; ++j) {
                    if (resolved[j] == collision_set[i].sprite) {
                        skip = true;
                        break;
                    }
                }
                if (!skip) {
                    vec_3_reflect(
                        vel,
                        collision_set[i].sprite->vel,
                        normals + (collision_set[i].mode_a - 1) * 3
                    );
                    float factor = 2.0f;
                    if (collision_set[i].other_sprite->is_static) {
                        factor = 1.0f;
                    }
                    vec_3_mul_scalar(
                        vel,
                        vec_3_normalize(vel),
                        (vel_a_momentum + vel_b_momentum) / factor
                    );
                    collision_set[i].sprite->vel[0] = vel[0];
                    collision_set[i].sprite->vel[1] = vel[1];
                    collision_set[i].sprite->vel[2] = vel[2];
                    for (int j = 0; j < COLLISIONS_MAX; ++j) {
                        if (resolved[j] == NULL) {
                            resolved[j] = collision_set[i].sprite;
                            break;
                        }
                    }
                } else {
                    skip = false;
                }
            }
            if (!collision_set[i].other_sprite->is_static) {
                for (int j = 0; j < COLLISIONS_MAX && resolved[j] != NULL; ++j) {
                    if (resolved[j] == collision_set[i].other_sprite) {
                        skip = true;
                        break;
                    }
                }
                if (!skip) {
                    vec_3_reflect(
                        vel,
                        collision_set[i].other_sprite->vel,
                        normals + (collision_set[i].mode_b - 1) * 3
                    );
                    float factor = 2.0f;
                    if (collision_set[i].other_sprite->is_static) {
                        factor = 1.0f;
                    }
                    vec_3_mul_scalar(
                        vel,
                        vec_3_normalize(orig_vel),
                        (vel_a_momentum + vel_b_momentum) / factor
                    );
                    collision_set[i].other_sprite->vel[0] = vel[0];
                    collision_set[i].other_sprite->vel[1] = vel[1];
                    collision_set[i].other_sprite->vel[2] = vel[2];
                    for (int j = 0; j < COLLISIONS_MAX; ++j) {
                        if (resolved[j] == NULL) {
                            resolved[j] = collision_set[i].other_sprite;
                            break;
                        }
                    }
                }
                skip = false;
            }
        }
        for (int j = 0; j < COLLISIONS_MAX; ++j) {
            resolved[j] = NULL;
        }
        if (collision_count == 0) {
            for (int i = 0; i < sprite_count; ++i) {
                sprites[i]->pos[0] += sprites[i]->vel[0] * fmaxf(0.0f, (dt - processed_time) - 0.0000001f);
                sprites[i]->pos[1] += sprites[i]->vel[1] * fmaxf(0.0f, (dt - processed_time) - 0.0000001f);
                sprites[i]->pos[2] += sprites[i]->vel[2] * fmaxf(0.0f, (dt - processed_time) - 0.0000001f);
            }
            processed_time = dt;
        } else {
            processed_time += collision_set[0].time;
        }
        candidate_collision_count = 0;
        collision_count = 0;
    }
    return true;
}

SpriteCollider::~SpriteCollider()
{
    remove_sprites();
}