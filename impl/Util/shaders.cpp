#include "impl/Util/shaders.h"

static bool get_compile_successful(bool print, int shader_id, const char* shader_type) {
    int successful = 0;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &successful);
    if (print && successful == GL_FALSE) {
        int log_length = 0;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
        char* info_log = (char*)malloc(log_length + 1);
        glGetShaderInfoLog(shader_id, log_length, &log_length, info_log);
        printf("Error compiling %s:\n%s\n", shader_type, info_log);
        free(info_log);
        return false;
    }
    return true;
}

static bool get_link_successful(bool print, int program) {
    int link_successful = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &link_successful);
    if (print && link_successful == GL_FALSE) {
        int log_length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
        char* info_log = (char*)malloc(log_length + 1);
        glGetProgramInfoLog(program, log_length, &log_length, info_log);
        printf("%s\n", info_log);
        free(info_log);
        return false;
    }
    return true;
}

/*
 * Compile the shader programs
 */
int compile_shader_program(
    const char* v_shader,
    size_t v_shader_length,
    const char* f_shader,
    size_t f_shader_length,
    GLuint* program
 ) {
    GLuint v_shader_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v_shader_id, 1, &v_shader, (const GLint *)&v_shader_length);
    glCompileShader(v_shader_id);
    const char* shader_type = "vertex shader";
    if (!get_compile_successful(true, v_shader_id, shader_type)) {
        glDeleteShader(v_shader_id);
        return -1;
    }
    GLuint f_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f_shader_id, 1, &f_shader, (const GLint *)&f_shader_length);
    glCompileShader(f_shader_id);
    shader_type = "fragment shader";
    if (!get_compile_successful(true, f_shader_id, shader_type)) {
        glDeleteShader(v_shader_id);
        glDeleteShader(f_shader_id);
        return -1;
    }
    *program = glCreateProgram();
    glAttachShader(*program, v_shader_id);
    glAttachShader(*program, f_shader_id);
    glLinkProgram(*program);
    GLuint link_successful = get_link_successful(true, *program);
    if (link_successful == GL_FALSE) {
        glDeleteProgram(*program);
        glDeleteShader(v_shader_id);
        glDeleteShader(f_shader_id);
        return -1;
    }
    glDetachShader(*program, v_shader_id);
    glDetachShader(*program, f_shader_id);
    glDeleteShader(v_shader_id);
    glDeleteShader(f_shader_id);
    return 0;
}

int delete_shader_program(GLuint program) {
    glDeleteProgram(program);
    return 0;
}
