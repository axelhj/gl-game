/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   shaders.h
 * Author: axelhjelmqvist
 *
 * Created on den 13 januari 2017, 10:17
 */

#ifndef SHADERS_H
#define SHADERS_H

#include <cstdlib>
#include <stdio.h>
//#include <OpenGL/gl3.h>
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

