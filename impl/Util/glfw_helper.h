#ifndef GLFW_HELPER_H
#define GLFW_HELPER_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

extern int keys[7];

extern double mouse_pos[4];

extern bool init_gl(const char* window_title, const int window_width, const int window_height);

extern void terminate_gl();

extern void print_gl_error(GLenum error);

extern void pre_draw();

extern bool post_draw();

#endif /* GLFW_HELPER_H */
