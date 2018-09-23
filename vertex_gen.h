/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   vertex_gen.h
 * Author: axelhjelmqvist
 *
 * Created on den 16 januari 2017, 12:18
 */

#ifndef VERTEX_GEN_H
#define VERTEX_GEN_H

#include <GLFW/glfw3.h>
#include <math.h>
#include "util.h"

extern unsigned char* get_image_data(const char* imageName, int* imageWidth, int* imageHeight);

extern void delete_image_data(char* imageData);

extern void generate_vertexes(GLfloat** vertexData, GLfloat** texCoordData, GLfloat** normalData,
        unsigned char* imageData, int imageWidth, int imageHeight, int vertexesX, int vertexesY);

extern void free_vertexes(GLfloat* vertexData, GLfloat* normalData);

#endif /* VERTEX_GEN_H */

