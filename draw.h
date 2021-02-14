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

typedef struct draw_entity {
    GLuint program;
    int vertex_buffer_coordinate_count;
    int tex_coord_buffer_coordinate_count;
    int normal_buffer_coordinate_count;
    int vertex_buffer_elements_count;
    int tex_coord_buffer_elements_count;
    int normal_buffer_elements_count;
    int vertex_buffer_size;
    int tex_coord_buffer_size;
    int normal_buffer_size;
    GLuint texture_id;
    GLfloat* vertices;
    GLfloat* tex_coords;
    GLfloat* normals;
    GLuint vao;
    GLuint vbo[3];
    GLfloat model_mat[16];
    GLfloat view_mat[16];
    GLfloat projection_mat[16];
} DRAW_ENTITY;

extern int keys[7];

extern bool init_gl(const char* window_title, const int window_width, const int window_height);

extern void terminate_gl();

extern void set_square_vertex_data(DRAW_ENTITY* draw_entity);

extern bool load_gl(DRAW_ENTITY* draw_entity);

extern bool load_gl_texture(DRAW_ENTITY* draw_entity, const char* file_name);

extern bool unload_gl(DRAW_ENTITY* draw_entity);

extern bool unload_gl_texture(DRAW_ENTITY* draw_entity);

extern void print_gl_error(GLenum error);

extern void pre_draw();

extern bool post_draw();

extern void draw_gl(DRAW_ENTITY* draw_entity);

#endif /* DRAW_H */

