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
    normal = (model * view * vec4(normalAttr, 1)).xyz;\n\
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
    vec4 lightDirection = vec4(0.0, 0.5, -0.5, 0.0);\n\
    float angle = dot(vec4(0.0) - lightDirection, vec4(normal, 0.0));\n\
    if (angle < 0.0) {\n\
        angle = -angle;\n\
    }\n\
    vec4 texColor = texture(texture0, texCoord);\n\
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

static int program;

const static int vertexBufferCoordinateCount = 3;

const static int texCoordBufferCoordinateCount = 2;

const static int normalBufferCoordinateCount = 3;

const static int vertexBufferElementsCount = 6 * 3;

const static int texCoordBufferElementsCount = 6 * 2;

const static int normalBufferElementsCount = 6 * 3;

const static int vertexBufferSize = sizeof(GLfloat) * vertexBufferElementsCount;

const static int texCoordBufferSize = sizeof(GLfloat) * texCoordBufferElementsCount;

const static int normalBufferSize = sizeof(GLfloat) * normalBufferElementsCount;

static GLuint vao = 0;

static GLuint vbo[] = { 0, 0, 0 };

static GLfloat vertices[] = {
    0.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
};

static GLfloat texCoords[] = {
    0.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f
};

static GLfloat normals[] = {
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f
};

static GLfloat modelMat[16];

static GLfloat viewMat[16];

static GLfloat projectionMat[16];

static void initMatrices() {
    mat_identity(modelMat);
    mat_identity(viewMat);
    mat_perspective(projectionMat, 90.0f, 0.1f, 100.0f);
}

bool initGl() {
    bool successful = compileShaderProgram(vProgram, strlen(vProgram), fProgram, strlen(fProgram), &program) == 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    int imageWidth, imageHeight;
    const char* texImageName = "hill.png";
    unsigned char* image = get_image_data(texImageName, &imageWidth, &imageHeight);
    if (image == NULL) {
        printf("Image (%s) was null\n", texImageName);
        return false;
    }
    //generate_vertexes(&vertices, &texCoords, &normals, image, imageWidth, imageHeight, MESH_WIDTH, MESH_HEIGHT);
    glGenBuffers(3, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, texCoordBufferSize, texCoords, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, normalBufferSize, normals, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    printGlError(glGetError());
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    initMatrices();
    return successful && loadGlTexture("ground.png");
}

static GLuint textureId;

bool loadGlTexture(const char* fileName) {
    int imageWidth, imageHeight;
    const unsigned char* imageData = get_image_data(fileName, &imageWidth, &imageHeight);
    // glActiveTexture(GL_TEXTURE_0); Is neccesary?
    glGenTextures(1, &textureId);
    printGlError(glGetError());
    glBindTexture(GL_TEXTURE_2D, textureId);
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureId);
    GLenum error = glGetError();
    printGlError(error);
    return error == GL_NO_ERROR;
}

static float pos[3] = {
    -0.495, 0.495, 0.198
};

void updateGl(int* keys) {
    int l = keys[0];
    int r = keys[1];
    int u = keys[2];
    int d = keys[3];
    int a = keys[4];
    int b = keys[5];
    float rate = 3.0 * 0.0165;
    if (u) {
        pos[0] += rate;
    } else if (d) {
        pos[0] -= rate;
    }
    if (l) {
        pos[1] += rate;
    } else if (r) {
        pos[1] -= rate;
    }
    if (a) {
        pos[2] += rate;
    } else if (b) {
        pos[2] -= rate;
    }
    mat_translation(modelMat, pos[0], pos[1], pos[2]);
    GLfloat* intermediate = (float*)malloc(sizeof(float)*16);
    mat_rot_x(intermediate, 3.1415f / 2.0f);
    GLfloat* modelMatCopy = mat_copy(modelMat);
    mat_multiplicate(modelMatCopy, intermediate, modelMat);
    mat_destroy(modelMatCopy);
    mat_destroy(intermediate);
}

void drawGl() {
    glUseProgram(program);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBindVertexArray(vao);
    GLint uniformLoc = glGetUniformLocation(program, "model");
    if (uniformLoc != -1) {
        glUniformMatrix4fv(uniformLoc, 1, false, modelMat);
    }
    uniformLoc = glGetUniformLocation(program, "view");
    if (uniformLoc != -1) {
        glUniformMatrix4fv(uniformLoc, 1, false, viewMat);
    }
    uniformLoc = glGetUniformLocation(program, "projection");
    if (uniformLoc != -1) {
        glUniformMatrix4fv(uniformLoc, 1, false, projectionMat);
    }
    GLint vertexAttribPos = glGetAttribLocation(program, "vertexAttr");
    GLint texCoordAttribPos = glGetAttribLocation(program, "texCoordAttr");
    GLint normalAttribPos = glGetAttribLocation(program, "normalAttr");
    glEnableVertexAttribArray(vertexAttribPos);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(vertexAttribPos, // attrib array index
                          vertexBufferCoordinateCount, // vertex attrib coordinates count
                          GL_FLOAT, // type
                          GL_FALSE, // normalized
                          0, // stride
                          (void*)0); // vbo offset
    glEnableVertexAttribArray(texCoordAttribPos);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(texCoordAttribPos, // attrib array index
                          texCoordBufferCoordinateCount, // vertex attrib coordinates count
                          GL_FLOAT, // type
                          GL_FALSE, // normalized
                          0, // stride
                          (void*)0); // vbo offset
    glEnableVertexAttribArray(normalAttribPos);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glVertexAttribPointer(normalAttribPos, // attrib array index
                          normalBufferCoordinateCount, // vertex attrib coordinates count
                          GL_FLOAT, // type
                          GL_FALSE, // normalized
                          0, // stride
                          (void*)0); // vbo offset
    glBindTexture(GL_TEXTURE_2D, textureId);
    GLint uniformLocation = glGetUniformLocation(program, "texture0");
    glUniform1i(uniformLocation, 0);

    glDrawArrays(GL_TRIANGLES, 0, vertexBufferElementsCount / vertexBufferCoordinateCount);
    glDisableVertexAttribArray(vertexAttribPos);
    glDisableVertexAttribArray(normalAttribPos);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    printGlError(glGetError());
}
