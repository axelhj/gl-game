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

typedef struct game_entity {
    GLuint program;
    int vertexBufferCoordinateCount;
    int texCoordBufferCoordinateCount;
    int normalBufferCoordinateCount;
    int vertexBufferElementsCount;
    int texCoordBufferElementsCount;
    int normalBufferElementsCount;
    int vertexBufferSize;
    int texCoordBufferSize;
    int normalBufferSize;
    GLuint textureId;
    GLfloat* vertices;
    GLfloat* texCoords;
    GLfloat* normals;
    GLuint vao;
    GLuint vbo[3];
    GLfloat modelMat[16];
    GLfloat viewMat[16];
    GLfloat projectionMat[16];
} GAME_ENTITY;

extern void initSquare(GAME_ENTITY* gameEntity);

extern bool initGl(GAME_ENTITY* gameEntity);

extern bool loadGlTexture(GAME_ENTITY* gameEntity, const char* fileName);

extern void printGlError(GLenum error);

extern void updateGl(GAME_ENTITY* gameEntity, int* keys);

extern void drawGl(GAME_ENTITY* gameEntity);

#endif /* DRAW_H */

