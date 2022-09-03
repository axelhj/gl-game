#ifndef VERTEX_GEN_H
#define VERTEX_GEN_H

#include <GLFW/glfw3.h>
#include <math.h>
#include "impl/Util/noise.h"
#include "impl/Util/vec3.h"

extern unsigned char* get_image_data(const char* imageName, int* imageWidth, int* imageHeight);

extern void delete_image_data(unsigned char* imageData);

extern void generate_vertexes(GLfloat** vertexData, GLfloat** texCoordData, GLfloat** normalData,
        unsigned char* imageData, int imageWidth, int imageHeight, int vertexesX, int vertexesY);

extern void free_vertexes(GLfloat* vertexData, GLfloat* normalData);

#endif /* VERTEX_GEN_H */
