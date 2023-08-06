#ifndef TEXT_SPRITE_H
#define TEXT_SPRITE_H
#include <stddef.h>
#include "impl/Util/mat4.h"
#include "impl/Util/static_shader_draw.h"
#include "impl/Engine/sprite.h"

class TextSprite : Sprite {
public:
    TextSprite();
    void draw_text(const char* text, int wrapat, int row_count);
    ~TextSprite();
};

#endif /* TEXT_SPRITE_H */
