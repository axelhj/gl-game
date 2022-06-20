#include "impl/Engine/text_sprite.h"

static const char* text_sprite_file_name = "asset/asciiextse146-transp.png";

static void update_texture_mat(float* texture_transform_mat, float* pos, float* size)
{
    GLfloat intermediate[16];
    GLfloat model_mat_copy[16];
    mat_scale(model_mat_copy, size[0], size[1], 1);
    mat_translation(intermediate, pos[0], pos[1], 0.0f);
    mat_multiplicate(model_mat_copy, intermediate, texture_transform_mat);
}

void TextSprite::draw_text(const char* text, int wrapat, int row_count)
{
    float original_x = pos[0];
    float original_y = pos[1];
    float sprite_width = size[0];
    float sprite_height = size[1];
    int sprite_file_letters_x = 17;
    int sprite_file_letters_y = 15;
    float tile_char_top_offset = 0.0f;
    float tile_char_left_offset = 0.0f;
    float tile_char_bottom_offset = 0.0f;
    float tile_char_right_offset = 0.0f;
    float tile_scale = 1.0f;
    float tile_width = (tile_scale / (float)sprite_file_letters_x);
    float tile_height = (tile_scale / (float)sprite_file_letters_y);
    float sprite_aspect =
        (tile_width * (1.0f - (tile_char_left_offset +
            tile_char_right_offset))) /
        (tile_height * (1.0f - (tile_char_top_offset +
            tile_char_bottom_offset)));
    float horizontal_sprite_offset_reduction = 0.15f;
    float vertical_sprite_offset_reduction = -0.3f;
    size[1] = sprite_height / sprite_aspect;
    float offset_values[4] = {};
    offset_values[2] = tile_width * (1.0f -
        (tile_char_left_offset + tile_char_right_offset));
    offset_values[3] = tile_height * (1.0f -
        (tile_char_top_offset + tile_char_bottom_offset));
    unsigned int c;
    for (int i = 0; text[i] != '\0'; ++i) {
        c = ((unsigned int)(unsigned char)text[i]);
        if (
            i < 0 ||
            i > (int)(0.5 + sprite_file_letters_x * sprite_file_letters_y)
        ) {
            offset_values[0] = offset_values[1] = 0;
        } else {
            offset_values[0] = (float)(c / sprite_file_letters_y) *
                tile_width + (tile_char_left_offset * tile_width);
            offset_values[1] = ((int)fmod(c, sprite_file_letters_y)) *
                tile_height + (tile_char_top_offset * tile_height);
        }
        pos[0] =
            original_y + ((int)fmod(i, -wrapat) *
            (1.0f - horizontal_sprite_offset_reduction) * sprite_width);
        pos[1] =
            original_x + (((int)i / -wrapat) *
            (1.0f - vertical_sprite_offset_reduction) * sprite_height);
        update_mat();
        update_texture_mat(
            draw->texture_transform_mat,
            offset_values,
            offset_values + 2
        );
        draw->draw_gl();
    }
    pos[0] = original_x;
    pos[1] = original_y;
    size[1] = sprite_height;
}

TextSprite::TextSprite() :
    Sprite(text_sprite_file_name)
{
}

TextSprite::~TextSprite()
{
}
