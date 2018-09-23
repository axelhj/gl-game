/* 
 * File:   shaders.cpp
 * Author: axelhjelmqvist
 *
 * Created on den 13 januari 2017, 10:18
 */

#include "shaders.h"

static bool getCompileSuccessful(bool print, int shaderId, const char* shaderType) {
    int successful = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &successful);
    if (print && successful == GL_FALSE) {
        int logLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
        char* infoLog = (char*)malloc(logLength + 1);
        glGetShaderInfoLog(shaderId, logLength, &logLength, infoLog);
        printf("Error compiling %s:\n%s\n", shaderType, infoLog);
        free(infoLog);
        return false;
    }
    return true;
}

static bool getLinkSuccessful(bool print, int program) {
    int linkSuccessful = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linkSuccessful);
    if (print && linkSuccessful == GL_FALSE) {
        int logLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        char* infoLog = (char*)malloc(logLength + 1);
        glGetProgramInfoLog(program, logLength, &logLength, infoLog);
        printf("%s\n", infoLog);
        free(infoLog);
        return false;
    }
    return true;
}

/*
 * Compile the shader programs
 */

int compileShaderProgram(const char* vShader, size_t vShaderLength, const char* fShader, size_t fShaderLength, GLuint* program) {
//    printf(">>%s<< %d\n", vShader, (int)vShaderLength);
//    printf(">>%s<< %d\n", fShader, (int)fShaderLength);
    int vShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShaderId, 1, &vShader, (const GLint *)&vShaderLength);
    glCompileShader(vShaderId);
    const char* shaderType = "vertex shader";
    if (!getCompileSuccessful(true, vShaderId, shaderType)) {
        glDeleteShader(vShaderId);
        return -1;
    }
    int fShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShaderId, 1, &fShader, (const GLint *)&fShaderLength);
    glCompileShader(fShaderId);
    shaderType = "fragment shader";
    if (!getCompileSuccessful(true, fShaderId, shaderType)) {
        glDeleteShader(vShaderId);
        glDeleteShader(fShaderId);
        return -1;
    }
    *program = glCreateProgram();
    glAttachShader(*program, vShaderId);
    glAttachShader(*program, fShaderId);
    glLinkProgram(*program);
    int linkSuccessful = getLinkSuccessful(true, *program);
    if (linkSuccessful == GL_FALSE) {
        glDeleteProgram(*program);
        glDeleteShader(vShaderId);
        glDeleteShader(fShaderId);
        return -1;
    }
    glDetachShader(*program, vShaderId);
    glDetachShader(*program, fShaderId);
    return 0;
}
