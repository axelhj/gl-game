#include "impl/Engine/sprite.h"

Sprite::Sprite(GLint texture_id) :
    pos {0.0f, 0.0f, 0.0f},
    vel {0.0f, 0.0f, 0.0f},
    size {0.0f, 0.0f }
{
    draw = new Draw();
    draw->set_square_vertex_data();
    draw->load_gl();
    draw->texture_id = texture_id;
}

Sprite::Sprite(const char* texture_name)
{
    draw = new Draw();
    draw->set_square_vertex_data();
    draw->load_gl();
    draw->load_gl_texture(texture_name);
}

void Sprite::set_pos(float x, float y, float z)
{
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
}

void Sprite::set_vel(float x, float y, float z)
{
    vel[0] = x;
    vel[1] = y;
    vel[2] = z;
}

void Sprite::set_size(float w, float h)
{
    size[0] = w;
    size[1] = h;
}

void Sprite::update_mat()
{
    GLfloat* model_mat = draw->model_mat;
    float* pos = this->pos;
    float* size = this->size;
    GLfloat intermediate[16];
    GLfloat model_mat_copy[16];
    mat_scale(model_mat_copy, size[0], size[1], 1);
    mat_translation(intermediate, pos[0], pos[1], pos[2]);
    mat_multiplicate(model_mat_copy, intermediate, model_mat);
}

void Sprite::update_mat(float* view_matrix, float* projection_matrix)
{
    mat_set_to(view_matrix, draw->view_mat);
    mat_set_to(projection_matrix, draw->projection_mat);
    update_mat();
}

Sprite::~Sprite()
{
    bool success = draw->unload_gl() || false;
    success = success && draw->unload_gl_texture();
    delete draw;
}
