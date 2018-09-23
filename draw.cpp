#include "draw.h"

static const char* vProgram =
"#version 150\n\
\n\
uniform vec3 rotate;\n\
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
    gl_Position = vec4(vertexAttr, 1);\n\
    float anglez = 3.1415 * 0.0;\n\
    float anglex = 3.1415 * 0.5;\n\
    gl_Position += vec4(-0.5, -0.5, -0.5, 0.0);\n\
    //gl_Position *= vec4(2.0, 2.0, 2.0, 1.0);\n\
    float x = gl_Position.x;\n\
    float y = gl_Position.y;\n\
    float z = gl_Position.z;\n\
    gl_Position.x = x * cos(rotate.z) - y * sin(rotate.z);\n\
    gl_Position.y = y * cos(rotate.z) + x * sin(rotate.z);\n\
    x = gl_Position.x;\n\
    y = gl_Position.y;\n\
    z = gl_Position.z;\n\
    gl_Position.y = y * cos(rotate.x) - z * sin(rotate.x);\n\
    gl_Position.z = y * sin(rotate.x) + z * cos(rotate.x);\n\
    x = gl_Position.x;\n\
    y = gl_Position.y;\n\
    z = gl_Position.z;\n\
    gl_Position.z = z * cos(rotate.y) - x * sin(rotate.y);\n\
    gl_Position.x = z * sin(rotate.y) + x * cos(rotate.y);\n\
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

static GLfloat vertices[] = {
    -1.0f, -1.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    -1.0f, 1.0f, 0.0f
};

#define MESH_WIDTH 150
#define MESH_HEIGHT 150

const static int vertexBufferCoordinateCount = 3;

const static int texCoordBufferCoordinateCount = 2;

const static int normalBufferCoordinateCount = 3;

const static int vertexBufferElementsCount = MESH_WIDTH * MESH_HEIGHT * 6 * 3;

const static int texCoordBufferElementsCount = MESH_WIDTH * MESH_HEIGHT * 6 * 2;

const static int normalBufferElementsCount = MESH_WIDTH * MESH_HEIGHT * 6 * 3;

const static int vertexBufferSize = sizeof(GLfloat) * vertexBufferElementsCount;

const static int texCoordBufferSize = sizeof(GLfloat) * texCoordBufferElementsCount;

const static int normalBufferSize = sizeof(GLfloat) * normalBufferElementsCount;

static GLuint vao = 0;

static GLuint vbo[] = { 0, 0, 0 };

bool initGl() {
    bool successful = compileShaderProgram(vProgram, strlen(vProgram), fProgram, strlen(fProgram), &program) == 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    GLfloat* vertices;
    GLfloat* texCoords;
    GLfloat* normals;
    int imageWidth, imageHeight;
    const char* texImageName = "hill.png";
    unsigned char* image = get_image_data(texImageName, &imageWidth, &imageHeight);
    if (image == NULL) {
        printf("Image (%s) was null\n", texImageName);
        return false;
    }
    generate_vertexes(&vertices, &texCoords, &normals, image, imageWidth, imageHeight, MESH_WIDTH, MESH_HEIGHT);
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
    return successful;
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

static GLfloat rotation[] = { 1, 2.5, 3.5 };

void updateGl(int* keys) {
    int l = keys[0];
    int r = keys[1];
    int u = keys[2];
    int d = keys[3];
    int a = keys[4];
    int b = keys[5];
    float rate = 3.0 * 0.0165;
    if (u) {
        rotation[0] += rate;
    } else if (d) {
        rotation[0] -= rate;
    }
    if (l) {
        rotation[1] += rate;
    } else if (r) {
        rotation[1] -= rate;
    }
    if (a) {
        rotation[2] += rate;
    } else if (b) {
        rotation[2] -= rate;
    }
}

void drawGl() {
    glUseProgram(program);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBindVertexArray(vao);
    GLint uniformLoc = glGetUniformLocation(program, "rotate");
    if (uniformLoc != -1) {
        glUniform3f(uniformLoc, rotation[0], rotation[1], rotation[2]);
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
