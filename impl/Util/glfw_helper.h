#ifndef GLFW_HELPER_H
#define GLFW_HELPER_H
#include <stdio.h>
#include <string.h>
//#include <OpenGL/gl3.h>
//#include <GL/gl.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "impl/Util/shaders.h"
#include "impl/Util/vertex_gen.h"
#include "impl/Util/draw.h"
#include "impl/Util/mat4.h"

extern int keys[7];

extern bool init_gl(const char* window_title, const int window_width, const int window_height);

extern void terminate_gl();

extern void print_gl_error(GLenum error);

extern void pre_draw();

extern bool post_draw();

#endif /* GLFW_HELPER_H */
