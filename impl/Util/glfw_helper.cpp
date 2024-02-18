#include "glfw_helper.h"

#include <stdio.h>
#include <string.h>

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

static int window_size[2] = { 0, 0 };
double mouse_pos[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
static void cursor_position_callback(double x_pos, double y_pos) {
    float previous_mouse_pos[2];
    previous_mouse_pos[0] = mouse_pos[0];
    previous_mouse_pos[1] = mouse_pos[1];
    mouse_pos[0] = x_pos / (float)window_size[0];
    mouse_pos[1] = y_pos / (float)window_size[1];
    mouse_pos[2] = mouse_pos[0] - previous_mouse_pos[0];
    mouse_pos[3] = mouse_pos[1] - previous_mouse_pos[1];
}

bool init_gl(const char* window_title, const int window_width, const int window_height) {
    if (!glfwInit()) {
        printf("Init failed\n");
        return false;
    }
    window_size[0] = window_width;
    window_size[1] = window_height;
    bool initSuccessful = true;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(window_width, window_height, window_title, NULL, NULL);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
    printf(
        "Init GL Ver: %s, (Major: %d, Min: %d)\n\n",
        glGetString(GL_VERSION),
        majorVersion,
        minorVersion
    );
    glViewport(0, 0, window_width, window_height);
    glClearColor(0.4f, 0.65f, 0.85f, 1.0f);
    return window != NULL && initSuccessful;
}

void terminate_gl() {
    glfwTerminate();
}

void pre_draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    double mouse_pos[2];
    glfwGetCursorPos(window, &mouse_pos[0], &mouse_pos[1]);
    cursor_position_callback(mouse_pos[0], mouse_pos[1]);
}

bool post_draw() {
    glfwSwapBuffers(window);
    glfwPollEvents();
    return glfwWindowShouldClose(window) == 0;
}
