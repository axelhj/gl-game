#include "text_sprite.h"

static const char* text_sprite_file_name = "asciiextse146-transp.png";

static void update_texture_mat(float* texture_transform_mat, float* pos, float* size)
{
    GLfloat intermediate[16];
    GLfloat model_mat_copy[16];
    mat_scale(model_mat_copy, size[0], size[1], 1);
    mat_translation(intermediate, pos[0], pos[1], 0.0f);
    mat_multiplicate(model_mat_copy, intermediate, texture_transform_mat);
}

bool create_text_sprite(SPRITE** sprite)
{
    return create_sprite(sprite, text_sprite_file_name);
}

bool destroy_text_sprite(SPRITE* sprite)
{
    return destroy_sprite(sprite);
}

void draw_sprite_text(SPRITE* sprite, const char* text, int wrapat)
{
    float original_x = sprite->pos[0];
    float original_y = sprite->pos[1];
    float sprite_width = sprite->size[0];
    float sprite_height = sprite->size[1];
    int letters_x = 8;
    int letters_y = 20;
    float tile_char_top_offset = 0.0f;
    float tile_char_left_offset = 0.05f;
    float tile_char_bottom_offset = 0.0f;
    float tile_char_right_offset = 0.5f;
    float tile_scale = 1.0f;
    float tile_width = 1.0f / (float)letters_x;
    float tile_height = 1.0f / (float)letters_y;
    float sprite_aspect =
        (tile_width * (1.0f - (tile_char_left_offset + tile_char_right_offset))) /
        (tile_height * (1.0f - (tile_char_top_offset + tile_char_bottom_offset)));
    float horizontal_sprite_offset_reduction = 0.15f;
    float vertical_sprite_offset_reduction = -0.3f;
    sprite->size[1] = sprite_height / sprite_aspect;
    float offset_values[4] = {};
    offset_values[2] = tile_width * (1.0f - (tile_char_left_offset + tile_char_right_offset));
    offset_values[3] = tile_height * (1.0f - (tile_char_top_offset + tile_char_bottom_offset));;
    for (unsigned int i = 0, c; text[i] != NULL; ++i) {
        c = text[i] - 32;
        if (i < 0 || i > (int)(0.5 + letters_x * letters_y)) {
            offset_values[0] = offset_values[1] = 0;
        } else {
            offset_values[0] = (float)((int)c / letters_y) * tile_width + (tile_char_left_offset * tile_width);
            offset_values[1] = (int)fmod((int)c, letters_y) * tile_height + (tile_char_top_offset * tile_height);
        }
        sprite->pos[0] =
            original_y + ((int)fmod(i, -wrapat) *
            (1.0f - horizontal_sprite_offset_reduction) * sprite_width);
        sprite->pos[1] =
            original_x + (((int)i / -wrapat) *
            (1.0f - vertical_sprite_offset_reduction) * sprite_height);
        update_model_mat(sprite);
        update_texture_mat(
            sprite->draw_entity->texture_transform_mat,
            offset_values,
            offset_values + 2);
        draw_gl(sprite->draw_entity);
    }
    sprite->pos[0] = original_x;
    sprite->pos[1] = original_y;
    sprite->size[1] = sprite_height;
}