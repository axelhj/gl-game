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

extern int compileShaderProgram(const char* vShader, size_t vShaderLength, const char* fShader, size_t fShaderLength, GLuint* program);

extern int deleteShaderProgram(GLuint program);

#endif /* SHADERS_H */

