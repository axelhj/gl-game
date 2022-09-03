#ifndef DRAW_H
#define DRAW_H
#include <stdio.h>
#include <string.h>
//#include <OpenGL/gl3.h>
//#include <GL/gl.h>
#include <GL/glew.h>
#include "impl/Util/glfw_helper.h"
#include "impl/Util/shaders.h"
#include "impl/Util/vertex_gen.h"
#include "impl/Util/draw.h"
#include "impl/Util/mat4.h"

class Draw {
public:
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
    GLfloat texture_transform_mat[16];
    Draw();
    ~Draw();
    void set_square_vertex_data();
    bool load_gl();
    bool load_gl_texture(const char* file_name);
    bool unload_gl();
    bool unload_gl_texture();
    void draw_gl();
};

#endif /* DRAW_H */

