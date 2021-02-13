#include "draw.h"

static const char* vProgram =
"#version 150\n\
\n\
uniform mat4 model;\n\
\n\
uniform mat4 view;\n\
\n\
uniform mat4 projection;\n\
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
    texCoord = texCoordAttr;\n\
}\n";

static const char* fProgram = 
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

void printGlError(GLenum error) {
    const char* errorString = NULL;
    if (error == GL_NO_ERROR) {
        //errorString = "GL_NO_ERROR";
    } else if (error == GL_INVALID_ENUM) {
        errorString = "GL_INVALID_ENUM";
    } else if (error == GL_INVALID_VALUE) {
        errorString = "GL_INVALID_VALUE";
    } else if (error == GL_INVALID_OPERATION) {
        errorString = "GL_INVALID_OPERATION";
    } else if (error == GL_INVALID_FRAMEBUFFER_OPERATION) {
        errorString = "GL_INVALID_FRAMEBUFFER_OPERATION";
    } else if (error == GL_OUT_OF_MEMORY) {
        errorString = "GL_OUT_OF_MEMORY";
    } else if (error == GL_STACK_UNDERFLOW) {
        errorString = "GL_STACK_UNDERFLOW";
    } else if (error == GL_STACK_OVERFLOW) {
        errorString = "GL_STACK_OVERFLOW";
    }
    if (errorString != NULL) {
        printf("%s\n", errorString);
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

bool initGl(const char* windowTitle, const int windowWidth, const int windowHeight) {
    if (!glfwInit()) {
        printf("Init failed\n");
        return false;
    }
    bool initSuccessful = true;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    GLenum error = glewInit();
    if (error != GL_NO_ERROR) {
        printf("Glew init failed\n");
        printGlError(error);
        initSuccessful = false;
    }
    int majorVersion = 0;
    int minorVersion = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
    printf("Init GL Ver: %s, (Major: %d, Min: %d)\n\n", glGetString(GL_VERSION), majorVersion, minorVersion);
    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(0.4f, 0.65f, 0.85f, 1.0f);
    return window != NULL && initSuccessful;
}

void terminateGl() {
    glfwTerminate();
}

static GLfloat squareVertices[] = {
    0.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
};

static GLfloat squareTexCoords[] = {
    0.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f
};

static GLfloat squareNormals[] = {
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f
};

void setSquareVertexData(DRAW_ENTITY* drawEntity) {
    drawEntity->vertexBufferCoordinateCount = 3;
    drawEntity->texCoordBufferCoordinateCount = 2;
    drawEntity->normalBufferCoordinateCount = 3;
    drawEntity->vertexBufferElementsCount = 3 * 6;
    drawEntity->texCoordBufferElementsCount = 2 * 6;
    drawEntity->normalBufferElementsCount = 3 * 6;
    drawEntity->vertexBufferSize = sizeof(GLfloat) * drawEntity->vertexBufferElementsCount;
    drawEntity->texCoordBufferSize = sizeof(GLfloat) * drawEntity->texCoordBufferElementsCount;
    drawEntity->normalBufferSize = sizeof(GLfloat) * drawEntity->normalBufferElementsCount;
    drawEntity->vertices = squareVertices;
    drawEntity->texCoords = squareTexCoords;
    drawEntity->normals = squareNormals;
}

bool loadGl(DRAW_ENTITY* drawEntity) {
    bool successful = compileShaderProgram(vProgram, strlen(vProgram), fProgram, strlen(fProgram), &drawEntity->program) == 0;
    glGenVertexArrays(1, &drawEntity->vao);
    glBindVertexArray(drawEntity->vao);
//    int imageWidth, imageHeight;
//    const char* texImageName = "hill.png";
//    unsigned char* image = get_image_data(texImageName, &imageWidth, &imageHeight);
//    if (image == NULL) {
//        printf("Image (%s) was null\n", texImageName);
//        return false;
//    }
    //generate_vertexes(&vertices, &texCoords, &normals, image, imageWidth, imageHeight, MESH_WIDTH, MESH_HEIGHT);
    glGenBuffers(3, drawEntity->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, drawEntity->vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, drawEntity->vertexBufferSize, drawEntity->vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, drawEntity->vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, drawEntity->texCoordBufferSize, drawEntity->texCoords, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, drawEntity->vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, drawEntity->normalBufferSize, drawEntity->normals, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    printGlError(glGetError());
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    mat_identity(drawEntity->modelMat);
    mat_identity(drawEntity->viewMat);
    mat_perspective(drawEntity->projectionMat, 90.0f, 0.1f, 100.0f);

    return successful;
}

bool loadGlTexture(DRAW_ENTITY* drawEntity, const char* fileName) {
    int imageWidth, imageHeight;
    const unsigned char* imageData = get_image_data(fileName, &imageWidth, &imageHeight);
    // glActiveTexture(GL_TEXTURE_0); Is neccesary?
    glGenTextures(1, &drawEntity->textureId);
    printGlError(glGetError());
    glBindTexture(GL_TEXTURE_2D, drawEntity->textureId);
    printGlError(glGetError());
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA8,
        imageWidth,
        imageHeight,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        imageData
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, drawEntity->textureId);
    GLenum error = glGetError();
    printGlError(error);
    return error == GL_NO_ERROR;
}

void preDraw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool postDraw() {
    glfwSwapBuffers(window);
    glfwPollEvents();
    return glfwWindowShouldClose(window) == 0;
}

void drawGl(DRAW_ENTITY* drawEntity) {
    glUseProgram(drawEntity->program);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBindVertexArray(drawEntity->vao);
    GLint uniformLoc = glGetUniformLocation(drawEntity->program, "model");
    if (uniformLoc != -1) {
        glUniformMatrix4fv(uniformLoc, 1, false, drawEntity->modelMat);
    }
    uniformLoc = glGetUniformLocation(drawEntity->program, "view");
    if (uniformLoc != -1) {
        glUniformMatrix4fv(uniformLoc, 1, false, drawEntity->viewMat);
    }
    uniformLoc = glGetUniformLocation(drawEntity->program, "projection");
    if (uniformLoc != -1) {
        glUniformMatrix4fv(uniformLoc, 1, false, drawEntity->projectionMat);
    }
    GLint vertexAttribPos = glGetAttribLocation(drawEntity->program, "vertexAttr");
    GLint texCoordAttribPos = glGetAttribLocation(drawEntity->program, "texCoordAttr");
    GLint normalAttribPos = glGetAttribLocation(drawEntity->program, "normalAttr");
    glEnableVertexAttribArray(vertexAttribPos);
    glBindBuffer(GL_ARRAY_BUFFER, drawEntity->vbo[0]);
    glVertexAttribPointer(vertexAttribPos, // attrib array index
        drawEntity->vertexBufferCoordinateCount, // vertex attrib coordinates count
        GL_FLOAT, // type
        GL_FALSE, // normalized
        0, // stride
        (void*)0); // vbo offset
    glEnableVertexAttribArray(texCoordAttribPos);
    glBindBuffer(GL_ARRAY_BUFFER, drawEntity->vbo[1]);
    glVertexAttribPointer(texCoordAttribPos, // attrib array index
        drawEntity->texCoordBufferCoordinateCount, // vertex attrib coordinates count
        GL_FLOAT, // type
        GL_FALSE, // normalized
        0, // stride
        (void*)0); // vbo offset
    glEnableVertexAttribArray(normalAttribPos);
    glBindBuffer(GL_ARRAY_BUFFER, drawEntity->vbo[2]);
    glVertexAttribPointer(normalAttribPos, // attrib array index
                          drawEntity->normalBufferCoordinateCount, // vertex attrib coordinates count
                          GL_FLOAT, // type
                          GL_FALSE, // normalized
                          0, // stride
                          (void*)0); // vbo offset
    glBindTexture(GL_TEXTURE_2D, drawEntity->textureId);
    GLint uniformLocation = glGetUniformLocation(drawEntity->program, "texture0");
    glUniform1i(uniformLocation, 0);
    glDrawArrays(GL_TRIANGLES, 0, drawEntity->vertexBufferElementsCount / drawEntity->vertexBufferCoordinateCount);
    glDisableVertexAttribArray(vertexAttribPos);
    glDisableVertexAttribArray(normalAttribPos);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    printGlError(glGetError());
}
