#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>
#include "impl/Util/draw.h"
#include "impl/Util/mat4.h"

class Sprite {
public:
    Sprite();
    Sprite(const char* textureName);
    void set_pos(float x, float y, float z);
    void set_vel(float x, float y, float z);
    void set_size(float w, float h);
    void update_mat();
    ~Sprite();
    bool is_static;
    float pos[3];
    float vel[3];
    float size[2];
    Draw* draw;
private:
};

#endif /* SPRITE_H */
