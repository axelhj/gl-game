#ifndef TEXT_SPRITE_H
#define TEXT_SPRITE_H

#include "impl/Engine/sprite.h"

class TextSprite : Sprite {
public:
    TextSprite();
    void draw_text(const char* text, int wrapat, int row_count);
    ~TextSprite();
};

#endif /* TEXT_SPRITE_H */
