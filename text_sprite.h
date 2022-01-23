/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   draw.h
 * Author: axelhjelmqvist
 *
 * Created on den 13 januari 2017, 14:32
 */

#ifndef TEXT_SPRITE_H
#define TEXT_SPRITE_H
#include <stddef.h>
#include "mat4.h"
#include "draw.h"
#include "sprite.h"

class TextSprite : Sprite {
public:
    TextSprite();
    void draw_text(const char* text, int wrapat, int row_count);
    ~TextSprite();
};

#endif /* TEXT_SPRITE_H */

