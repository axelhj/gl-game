#include "impl/Util/draw.h"

static const char* v_program =
"#version 150\n\
\n\
uniform mat4 model;\n\
\n\
uniform mat4 view;\n\
\n\
uniform mat4 projection;\n\
\n\
uniform mat4 textureTransform;\n\
\n\
in vec3 vertexAttr;\n\
\n\
in vec2 texCoordAttr;\n\
\n\
in vec3 normalAttr;\n\
\n\
out vec2 texCoord;\n\
\n\
out vec3 normal;\n\
\n\
void main(void) {\n\
    normal = normalAttr;\n\
    gl_Position = vec4(vertexAttr, 1) * model * view * projection;\n\
    normal = vec4(normalAttr, 0).xyz;\n\
    texCoord = (vec4(texCoordAttr, 0, 1) * textureTransform).xy;\n\
}\n";

static const char* f_program =
"#version 150\n\
\n\
in vec2 texCoord;\n\
\n\
in vec3 normal;\n\
\n\
uniform sampler2D texture0;\n\
\n\
out vec4 fragColor;\
\n\
void main(void) {\n\
    vec4 texColor = texture(texture0, texCoord);\n\
    if (texColor.a < 0.005) {\n\
        discard;\n\
    }\n\
    vec4 lightDirection = vec4(0.0, 0.5, -0.5, 0.0);\n\
    float angle = dot(vec4(0.0) - lightDirection, vec4(normal, 0.0));\n\
    if (angle < 0.0) {\n\
        angle = -angle;\n\
    }\n\
    fragColor = vec4(angle * texColor.rgb, texColor.a);\n\
}\n";

void print_gl_error(GLenum error) {
    const char* error_string = NULL;
    if (error == GL_NO_ERROR) {
        //error_string = "GL_NO_ERROR";
    } else if (error == GL_INVALID_ENUM) {
        error_string = "GL_INVALID_ENUM";
    } else if (error == GL_INVALID_VALUE) {
        error_string = "GL_INVALID_VALUE";
    } else if (error == GL_INVALID_OPERATION) {
        error_string = "GL_INVALID_OPERATION";
    } else if (error == GL_INVALID_FRAMEBUFFER_OPERATION) {
        error_string = "GL_INVALID_FRAMEBUFFER_OPERATION";
    } else if (error == GL_OUT_OF_MEMORY) {
        error_string = "GL_OUT_OF_MEMORY";
    } else if (error == GL_STACK_UNDERFLOW) {
        error_string = "GL_STACK_UNDERFLOW";
    } else if (error == GL_STACK_OVERFLOW) {
        error_string = "GL_STACK_OVERFLOW";
    }
    if (error_string != NULL) {
        printf("%s\n", error_string);
    }
}

static GLFWwindow* window;
int keys[7] = {0, 0, 0, 0, 0, 0, 0};
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        printf("Esc pressed\n");
        keys[6] = 1;
    } else if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
        printf("Esc released\n");
        keys[6] = 0;
    } else if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        printf("Q pressed\n");
        keys[6] = 1;
    } else if (key == GLFW_KEY_Q && action == GLFW_RELEASE) {
        printf("Q released\n");
        keys[6] = 0;
    } else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        keys[0] = 1;
    } else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
        keys[0] = 0;
    } else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        keys[1] = 1;
    } else if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
        keys[1] = 0;
    } else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        keys[2] = 1;
    } else if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
        keys[2] = 0;
    } else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        keys[3] = 1;
    } else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
        keys[3] = 0;
    } else if (key == GLFW_KEY_X && action == GLFW_PRESS) {
        keys[4] = 1;
    } else if (key == GLFW_KEY_X && action == GLFW_RELEASE) {
        keys[4] = 0;
    } else if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
        keys[5] = 1;
    } else if (key == GLFW_KEY_Z && action == GLFW_RELEASE) {
        keys[5] = 0;
    } else if (action != GLFW_REPEAT) {
        printf("Unknown key %d, action %d\n", key, action);
    }
}

Draw::Draw()
{
}

Draw::~Draw() {
}

bool init_gl(const char* window_title, const int window_width, const int window_height) {
    if (!glfwInit()) {
        printf("Init failed\n");
        return false;
    }
    bool initSuccessful = true;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(window_width, window_height, window_title, NULL, NULL);
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    GLenum error = glewInit();
    if (error != GL_NO_ERROR) {
        printf("Glew init failed\n");
        print_gl_error(error);
        initSuccessful = false;
    }
    int majorVersion = 0;
    int minorVersion = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
    printf("Init GL Ver: %s, (Major: %d, Min: %d)\n\n", glGetString(GL_VERSION), majorVersion, minorVersion);
    glViewport(0, 0, window_width, window_height);
    glClearColor(0.4f, 0.65f, 0.85f, 1.0f);
    return window != NULL && initSuccessful;
}

void terminate_gl() {
    glfwTerminate();
}

void pre_draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool post_draw() {
    glfwSwapBuffers(window);
    glfwPollEvents();
    return glfwWindowShouldClose(window) == 0;
}

static GLfloat square_vertices[] = {
    0.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
};

static GLfloat square_text_coords[] = {
    0.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f
};

static GLfloat square_normals[] = {
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f
};

void Draw::set_square_vertex_data() {
    vertex_buffer_coordinate_count = 3;
    tex_coord_buffer_coordinate_count = 2;
    normal_buffer_coordinate_count = 3;
    vertex_buffer_elements_count = 3 * 6;
    tex_coord_buffer_elements_count = 2 * 6;
    normal_buffer_elements_count = 3 * 6;
    vertex_buffer_size = sizeof(GLfloat) * vertex_buffer_elements_count;
    tex_coord_buffer_size = sizeof(GLfloat) * tex_coord_buffer_elements_count;
    normal_buffer_size = sizeof(GLfloat) * normal_buffer_elements_count;
    vertices = square_vertices;
    tex_coords = square_text_coords;
    normals = square_normals;
}

bool Draw::load_gl() {
    bool successful = compile_shader_program(v_program, strlen(v_program), f_program, strlen(f_program), &program) == 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(3, vbo);
    // Note: glBufferData can cause GL_OUT_OF_MEMORY error.
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, vertices, GL_STATIC_DRAW);
    print_gl_error(glGetError());
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, tex_coord_buffer_size, tex_coords, GL_STATIC_DRAW);
    print_gl_error(glGetError());
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, normal_buffer_size, normals, GL_STATIC_DRAW);
    print_gl_error(glGetError());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    mat_identity(model_mat);
    mat_identity(view_mat);
    mat_perspective(projection_mat, 90.0f, 0.1f, 100.0f);
    mat_identity(texture_transform_mat);
    return successful;
}

bool Draw::load_gl_texture(const char* file_name) {
    int image_width, image_height;
    unsigned char* imageData = get_image_data(file_name, &image_width, &image_height);
    glGenTextures(1, &texture_id);
    print_gl_error(glGetError());
    glBindTexture(GL_TEXTURE_2D, texture_id);
    print_gl_error(glGetError());
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA8,
        image_width,
        image_height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        imageData
    );
    delete_image_data(imageData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    Not used since filter parameter is GL_NEAREST.
//    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    GLenum error = glGetError();
    print_gl_error(error);
    return error == GL_NO_ERROR;
}

extern bool Draw::unload_gl()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(3, vbo);
    glBindVertexArray(0);
    delete_shader_program(program);
    glDeleteVertexArrays(1, &vao);
    return true;
}

extern bool Draw::unload_gl_texture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &texture_id);
    return true;
}

void Draw::draw_gl() {
    glUseProgram(program);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBindVertexArray(vao);
    GLint uniform_loc = glGetUniformLocation(program, "model");
    if (uniform_loc != -1) {
        glUniformMatrix4fv(uniform_loc, 1, false, model_mat);
    }
    uniform_loc = glGetUniformLocation(program, "view");
    if (uniform_loc != -1) {
        glUniformMatrix4fv(uniform_loc, 1, false, view_mat);
    }
    uniform_loc = glGetUniformLocation(program, "projection");
    if (uniform_loc != -1) {
        glUniformMatrix4fv(uniform_loc, 1, false, projection_mat);
    }
    uniform_loc = glGetUniformLocation(program, "textureTransform");
    if (uniform_loc != -1) {
        glUniformMatrix4fv(uniform_loc, 1, false, texture_transform_mat);
    }
    GLint vertex_attrib_pos = glGetAttribLocation(program, "vertexAttr");
    GLint tex_coord_attrib_pos = glGetAttribLocation(program, "texCoordAttr");
    GLint normal_attrib_pos = glGetAttribLocation(program, "normalAttr");
    glEnableVertexAttribArray(vertex_attrib_pos);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(vertex_attrib_pos, // attrib array index
        vertex_buffer_coordinate_count, // vertex attrib coordinates count
        GL_FLOAT, // type
        GL_FALSE, // normalized
        0, // stride
        (void*)0); // vbo offset
    glEnableVertexAttribArray(tex_coord_attrib_pos);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(tex_coord_attrib_pos, // attrib array index
        tex_coord_buffer_coordinate_count, // vertex attrib coordinates count
        GL_FLOAT, // type
        GL_FALSE, // normalized
        0, // stride
        (void*)0); // vbo offset
    glEnableVertexAttribArray(normal_attrib_pos);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glVertexAttribPointer(normal_attrib_pos, // attrib array index
        normal_buffer_coordinate_count, // vertex attrib coordinates count
        GL_FLOAT, // type
        GL_FALSE, // normalized
        0, // stride
        (void*)0); // vbo offset
    glBindTexture(GL_TEXTURE_2D, texture_id);
    GLint uniform_location = glGetUniformLocation(program, "texture0");
    glUniform1i(uniform_location, 0);
    glDrawArrays(GL_TRIANGLES, 0, vertex_buffer_elements_count / vertex_buffer_coordinate_count);
    glDisableVertexAttribArray(vertex_attrib_pos);
    glDisableVertexAttribArray(tex_coord_attrib_pos);
    glDisableVertexAttribArray(normal_attrib_pos);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    print_gl_error(glGetError());
}
