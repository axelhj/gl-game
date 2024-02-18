#ifndef SPRITE_H
#define SPRITE_H

#include <memory>
#include <GL/glew.h>
#include "impl/Util/static_shader_draw.h"

class Sprite {
public:
    Sprite(GLint texture_id);
    Sprite(const char* textureName);
    void set_pos(float x, float y, float z);
    void set_vel(float x, float y, float z);
    void set_size(float w, float h);
    void update_mat();
    void update_mat(float* view_matrix, float* projection_matrix);
    ~Sprite();
    bool is_static;
    float pos[3];
    float vel[3];
    float size[2];
    std::shared_ptr<Draw> draw;
private:
};

#endif /* SPRITE_H */
