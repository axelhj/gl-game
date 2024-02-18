#ifndef STATIC_SHADER_DRAW_H
#define STATIC_SHADER_DRAW_H
#include <GL/glew.h>

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

#endif /* STATIC_SHADER_DRAW_H */

