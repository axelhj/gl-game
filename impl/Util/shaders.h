#ifndef SHADERS_H
#define SHADERS_H

#include <cstdlib>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

extern int compile_shader_program(
    const char* v_shader,
    size_t v_shader_lenght,
    const char* f_shader,
    size_t f_shader_length,
    GLuint* program
);

extern int delete_shader_program(GLuint program);

#endif /* SHADERS_H */

