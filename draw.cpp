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

static GLfloat squareVertices[] = {
    0.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
};

static GLfloat squareTexCoords[] = {
    0.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f
};

static GLfloat squareNormals[] = {
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f
};

void initSquare(GAME_ENTITY* gameEntity) {
    gameEntity->vertexBufferCoordinateCount = 3;
    gameEntity->texCoordBufferCoordinateCount = 2;
    gameEntity->normalBufferCoordinateCount = 3;
    gameEntity->vertexBufferElementsCount = 3 * 6;
    gameEntity->texCoordBufferElementsCount = 2 * 6;
    gameEntity->normalBufferElementsCount = 3 * 6;
    gameEntity->vertexBufferSize = sizeof(GLfloat) * gameEntity->vertexBufferElementsCount;
    gameEntity->texCoordBufferSize = sizeof(GLfloat) * gameEntity->texCoordBufferElementsCount;
    gameEntity->normalBufferSize = sizeof(GLfloat) * gameEntity->normalBufferElementsCount;
    gameEntity->vertices = squareVertices;
    gameEntity->texCoords = squareTexCoords;
    gameEntity->normals = squareNormals;
}

bool initGl(GAME_ENTITY* gameEntity) {
    bool successful = compileShaderProgram(vProgram, strlen(vProgram), fProgram, strlen(fProgram), &gameEntity->program) == 0;
    glGenVertexArrays(1, &gameEntity->vao);
    glBindVertexArray(gameEntity->vao);
//    int imageWidth, imageHeight;
//    const char* texImageName = "hill.png";
//    unsigned char* image = get_image_data(texImageName, &imageWidth, &imageHeight);
//    if (image == NULL) {
//        printf("Image (%s) was null\n", texImageName);
//        return false;
//    }
    //generate_vertexes(&vertices, &texCoords, &normals, image, imageWidth, imageHeight, MESH_WIDTH, MESH_HEIGHT);
    glGenBuffers(3, gameEntity->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, gameEntity->vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, gameEntity->vertexBufferSize, gameEntity->vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, gameEntity->vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, gameEntity->texCoordBufferSize, gameEntity->texCoords, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, gameEntity->vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, gameEntity->normalBufferSize, gameEntity->normals, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    printGlError(glGetError());
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    mat_identity(gameEntity->modelMat);
    mat_identity(gameEntity->viewMat);
    mat_perspective(gameEntity->projectionMat, 90.0f, 0.1f, 100.0f);

    return successful;
}

bool loadGlTexture(GAME_ENTITY* gameEntity, const char* fileName) {
    int imageWidth, imageHeight;
    const unsigned char* imageData = get_image_data(fileName, &imageWidth, &imageHeight);
    // glActiveTexture(GL_TEXTURE_0); Is neccesary?
    glGenTextures(1, &gameEntity->textureId);
    printGlError(glGetError());
    glBindTexture(GL_TEXTURE_2D, gameEntity->textureId);
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
    glBindTexture(GL_TEXTURE_2D, gameEntity->textureId);
    GLenum error = glGetError();
    printGlError(error);
    return error == GL_NO_ERROR;
}

void drawGl(GAME_ENTITY* gameEntity) {
    glUseProgram(gameEntity->program);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBindVertexArray(gameEntity->vao);
    GLint uniformLoc = glGetUniformLocation(gameEntity->program, "model");
    if (uniformLoc != -1) {
        glUniformMatrix4fv(uniformLoc, 1, false, gameEntity->modelMat);
    }
    uniformLoc = glGetUniformLocation(gameEntity->program, "view");
    if (uniformLoc != -1) {
        glUniformMatrix4fv(uniformLoc, 1, false, gameEntity->viewMat);
    }
    uniformLoc = glGetUniformLocation(gameEntity->program, "projection");
    if (uniformLoc != -1) {
        glUniformMatrix4fv(uniformLoc, 1, false, gameEntity->projectionMat);
    }
    GLint vertexAttribPos = glGetAttribLocation(gameEntity->program, "vertexAttr");
    GLint texCoordAttribPos = glGetAttribLocation(gameEntity->program, "texCoordAttr");
    GLint normalAttribPos = glGetAttribLocation(gameEntity->program, "normalAttr");
    glEnableVertexAttribArray(vertexAttribPos);
    glBindBuffer(GL_ARRAY_BUFFER, gameEntity->vbo[0]);
    glVertexAttribPointer(vertexAttribPos, // attrib array index
        gameEntity->vertexBufferCoordinateCount, // vertex attrib coordinates count
        GL_FLOAT, // type
        GL_FALSE, // normalized
        0, // stride
        (void*)0); // vbo offset
    glEnableVertexAttribArray(texCoordAttribPos);
    glBindBuffer(GL_ARRAY_BUFFER, gameEntity->vbo[1]);
    glVertexAttribPointer(texCoordAttribPos, // attrib array index
        gameEntity->texCoordBufferCoordinateCount, // vertex attrib coordinates count
        GL_FLOAT, // type
        GL_FALSE, // normalized
        0, // stride
        (void*)0); // vbo offset
    glEnableVertexAttribArray(normalAttribPos);
    glBindBuffer(GL_ARRAY_BUFFER, gameEntity->vbo[2]);
    glVertexAttribPointer(normalAttribPos, // attrib array index
                          gameEntity->normalBufferCoordinateCount, // vertex attrib coordinates count
                          GL_FLOAT, // type
                          GL_FALSE, // normalized
                          0, // stride
                          (void*)0); // vbo offset
    glBindTexture(GL_TEXTURE_2D, gameEntity->textureId);
    GLint uniformLocation = glGetUniformLocation(gameEntity->program, "texture0");
    glUniform1i(uniformLocation, 0);
    glDrawArrays(GL_TRIANGLES, 0, gameEntity->vertexBufferElementsCount / gameEntity->vertexBufferCoordinateCount);
    glDisableVertexAttribArray(vertexAttribPos);
    glDisableVertexAttribArray(normalAttribPos);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    printGlError(glGetError());
}
