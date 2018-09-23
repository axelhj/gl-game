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

#ifndef DRAW_H
#define DRAW_H
#include <stdio.h>
#include <string.h>
//#include <OpenGL/gl3.h>
//#include <GL/gl.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shaders.h"
#include "vertex_gen.h"
#include "draw.h"
#include "mat4.h"

extern bool initGl();

extern bool loadGlTexture(const char* fileName);

extern void printGlError(GLenum error);

extern void updateGl(int* keys);

extern void drawGl();

#endif /* DRAW_H */

