#include "sprite_collider.h"

#define SPRITES_MAX 25
static int sprites_count = 0;

static SPRITE** sprites = NULL;

bool add_sprites(SPRITE** add_sprites, int count)
{
    int new_count = count + sprites_count;
    if (new_count> SPRITES_MAX) {
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

static float distance(SPRITE* sprite_a, SPRITE* sprite_b)
{
    float diff_x = sprite_b->pos[0] - sprite_a->pos[0];
    float diff_y = sprite_b->pos[1] - sprite_a->pos[1];
    return (float)sqrt(diff_x * diff_x - diff_y * diff_y);
}

const char* coll_mode_labels [8 + 1] = {
    "",
    "a right", // 1
    "a left", // 2
    "a top", // 3
    "a bottom" // 4
};

typedef struct collision_object {
    float pos[2];
    float vel[2];
    float size[2];
    int coll_mode;
} COLLISION_OBJECT;

static bool intersects(COLLISION_OBJECT* a, COLLISION_OBJECT* b)
{
    float left_a = a->pos[0];
    float left_b = b->pos[0];
    float right_a = a->pos[0] + a->size[0];
    float right_b = b->pos[0] + b->size[0];
    float top_a = a->pos[1] + a->size[1];
    float top_b = b->pos[1] + b->size[1];
    float bottom_a = a->pos[1];
    float bottom_b = b->pos[1];
    return (
        (left_a < right_b &&
        left_b < right_a) &&
        (right_a > left_b &&
        right_b > left_a) &&
        (top_a > bottom_b &&
        top_b > bottom_a) &&
        (bottom_a < top_b &&
        bottom_b < top_a)
    );
}

static float intersection_time(COLLISION_OBJECT* a, COLLISION_OBJECT* b)
{
    if (intersects(a, b)) {
        return 0;
    }
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

    float first_coll_time = FLT_MAX;
    float coll_time = 0;
    int coll_mode = 0;

    // right side A -- moving towards B?
    if (a_vel_x > 0 && right_a < left_b) {
        coll_time = (left_b - right_a) / (a_vel_x + b_vel_x);
        coll_time < 0 && printf("colltime 1 %f\n", coll_time);
        if (coll_time > 0 && coll_time < first_coll_time) {
            first_coll_time = coll_time;
            coll_mode = 1;
        }
    }
    // left side A -- moving towards B?
    if (a_vel_x < 0 && left_a > right_b) {
        coll_time = (right_b - left_a) / (a_vel_x - b_vel_x);
        coll_time < 0 && printf("colltime 2 %f\n", coll_time);
        if (coll_time > 0 && coll_time < first_coll_time) {
            first_coll_time = coll_time;
            coll_mode = 2;
        }
    }
    // top side A -- moving towards B?
    if (a_vel_y > 0 && top_a < bottom_b) {
        coll_time = (bottom_b - top_a) / (a_vel_y + b_vel_y);
        coll_time < 0 && printf("colltime 3 %f\n", coll_time);
        if (coll_time > 0 && coll_time < first_coll_time) {
            first_coll_time = coll_time;
            coll_mode = 3;
        }
    }
    // bottom side A -- moving towards B?
    if (a_vel_y < 0 && bottom_a > top_b) {
        coll_time = (top_b - bottom_a) / (a_vel_y - b_vel_y);
        coll_time < 0 && printf("colltime 4 %f\n", coll_time);
        if (coll_time > 0 && coll_time < first_coll_time) {
            first_coll_time = coll_time;
            coll_mode = 4;
        }
    }
    a->coll_mode = coll_mode;
    b->coll_mode = coll_mode;
    return first_coll_time;
}

static void advance_time(COLLISION_OBJECT* object, float time) {
    object->pos[0] += object->vel[0] * time;
    object->pos[1] += object->vel[1] * time;
}

static void copy_fields(SPRITE* source, COLLISION_OBJECT* target) {
    target->pos[0] = source->pos[0];
    target->pos[1] = source->pos[1];
    target->vel[0] = source->vel[0];
    target->vel[1] = source->vel[1];
    target->size[0] = source->size[0];
    target->size[1] = source->size[1];
}

static float find_collision_time(SPRITE* sprite, float dt)
{
    float time = dt + 1.0f;
    COLLISION_OBJECT a;
    COLLISION_OBJECT b;
    for (int i = 0; i < /*sprites_count*/2; ++i) {
        if (sprites[i] != sprite) {
            copy_fields(sprite, &a);
            copy_fields(sprites[i], &b);
            float collision_time = intersection_time(&a, &b);
            if (collision_time > 0 && collision_time < time) {
                advance_time(&a, collision_time);
                advance_time(&b, collision_time);
                if (intersects(&a, &b)) {
                    time = collision_time;
                }
            }
        }
    }
    if (time <= dt) {
        return time;
    }
    return -1;
}

bool process_sprites(float dt)
{
    float processed_time = 0;
    while (processed_time < dt) {
        float first_collision_time = -1;
        for (int i = 0; i < /*sprites_count*/1; ++i) {
            float time = find_collision_time(sprites[0], dt);
            if (time > -1 && (time > processed_time && processed_time + time <= dt)) {
                first_collision_time = time;
            }
        }
        processed_time =
            first_collision_time == -1 ?
            dt :
            processed_time + first_collision_time;
        if (first_collision_time != -1.0f) {
            for (int i = 0; i < sprites_count; ++i) {
                sprites[i]->pos[0] += sprites[i]->vel[0] * first_collision_time;
                sprites[i]->pos[1] += sprites[i]->vel[1] * first_collision_time;
                sprites[i]->pos[2] += sprites[i]->vel[2] * first_collision_time;
            }
            // Resolve collision by deducing collision mode to retrieve a collision normal.
//            printf("resolving %s\n", coll_mode_labels[0]);
            if (sprites[0]->vel[0] != 0) {
                sprites[0]->vel[0] *= -1;
            }
            if (sprites[0]->vel[1] != 0) {
                sprites[0]->vel[1] *= -1;
            }
        } else {
            for (int i = 0; i < sprites_count; ++i) {
                sprites[i]->pos[0] += sprites[i]->vel[0] * processed_time;
                sprites[i]->pos[1] += sprites[i]->vel[1] * processed_time;
                sprites[i]->pos[2] += sprites[i]->vel[2] * processed_time;
            }
        }
    }
    return true;
}
