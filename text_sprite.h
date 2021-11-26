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

bool create_text_sprite(SPRITE** sprite);

bool destroy_text_sprite(SPRITE* sprite);

void draw_sprite_text(SPRITE* sprite, const char* text, int wrapat);

#endif /* TEXT_SPRITE_H */

