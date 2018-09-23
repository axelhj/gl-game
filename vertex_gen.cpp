#include "vertex_gen.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned char* get_image_data(const char* filename, int* imageWidth, int* imageHeight) {
    int x, y, componentsPerPixel;
    unsigned char* data = stbi_load(filename, &x, &y, &componentsPerPixel, 4);
    /*ignore since components will correspond to 5th argument of stbi_load function
    if (componentsPerPixel != 4) {
        return NULL;
    }*/
    *imageWidth = x;
    *imageHeight = y;
    return data;
}

void delete_image_data(unsigned char* imageData) {
    stbi_image_free(imageData);
}

static GLfloat* vec3normalize(GLfloat* vec3) {
    float vecLength = (float)sqrt(vec3[0] * vec3[0] + vec3[1] * vec3[1] + vec3[2] * vec3[2]);
    if (vecLength == 0.0f) {
        return vec3;
    }
    vec3[0] /= vecLength;
    vec3[1] /= vecLength;
    vec3[2] /= vecLength;
    return vec3;
}

static GLfloat* vec3cross(GLfloat* res, GLfloat* vec3a, GLfloat* vec3b) {
    res[0] = vec3a[1] * vec3b[2] - vec3a[2] * vec3b[1];
    res[1] = vec3a[2] * vec3b[0] - vec3a[0] * vec3b[2];
    res[2] = vec3a[0] * vec3b[1] - vec3a[1] * vec3b[0];
    return res;
}

static GLfloat* vec3sub(GLfloat* res, GLfloat* vec3l, GLfloat* vec3r) {
    res[0] = vec3l[0] - vec3r[0];
    res[1] = vec3l[1] - vec3r[1];
    res[2] = vec3l[2] - vec3r[2];
    return res;
}

static void calculateNormal(GLfloat* normal, GLfloat* vertexA, GLfloat* vertexB, GLfloat* vertexC) {
    GLfloat tempVec[9];
    vec3cross(normal, vec3sub(tempVec + 3, vertexB, vertexA), vec3sub(tempVec + 6, vertexC, vertexA));
    vec3normalize(normal);
}

static float getHeightVal(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    return ((float)r / 255.0f) * ((float)g / 255.0f) * (255.0f / (float)b);
}

void generate_vertexes(GLfloat** vertexData, GLfloat** texCoordData, GLfloat** normalData,
        unsigned char* imageData, int imageWidth, int imageHeight, int vertexesX, int vertexesY
) {
    *vertexData = (GLfloat*)malloc(sizeof(GLfloat) * vertexesX * vertexesY * 3);
    float triangleWidth = ((float)imageWidth) / ((float)vertexesX);
    float triangleHeight = ((float)imageHeight) / ((float)vertexesY);
    for (int i = 0; i < vertexesX * vertexesY * 3; i += 3) {
        float x = (i / 3) % vertexesX;
        float y = (i / 3) / vertexesX;
        int imagePixelIndex = ((int)(x * triangleWidth) + ((int)(y * triangleHeight)) * imageWidth) * 4;
        if (imagePixelIndex >= imageWidth * imageHeight * 4 - 4) {
            imagePixelIndex = imageWidth * imageHeight * 4 - 4 - 1;
        }
        float vHeight = getHeightVal(
            imageData[imagePixelIndex + 0],
            imageData[imagePixelIndex + 1],
            imageData[imagePixelIndex + 2],
            imageData[imagePixelIndex + 3]
        );/**/
        /*float scaledX = (x) / ((float)vertexesX * 0.5f);
        float scaledY = (y) / ((float)vertexesY * 0.5f);
        float vHeight = perlin(scaledX, scaledY, 0);
        printf("%f %f\n", y, scaledY);
        */
         //vHeight = vHeight * 0.05f + 0.5f;
        (*vertexData)[i + 0] = (GLfloat)(x / (float)vertexesX);
        (*vertexData)[i + 1] = (GLfloat)vHeight;
        (*vertexData)[i + 2] = (GLfloat)(y / (float)vertexesY);
    }
    GLfloat* triangleVertexData;
    triangleVertexData = (GLfloat*)malloc(sizeof(GLfloat) * vertexesX * vertexesY * 3 * 6);
    for (int i = 0; i < vertexesX * vertexesY * 3 * 6; i += 3 * 6) {
        int x = (i / 18) % vertexesX;
        int y = (i / 18) / vertexesX;
        int vDataIndex = i / 6;
        if (x >= vertexesX - 1 || y >= vertexesY - 1) {
            GLfloat* ll = (*vertexData + vDataIndex);
            for (int j = 0; j < 6; ++j) {
                triangleVertexData[i + j * 3 + 0] = ll[0];
                triangleVertexData[i + j * 3 + 1] = ll[1];
                triangleVertexData[i + j * 3 + 2] = ll[2];
            }
            continue;
        }
        GLfloat* ll = (*vertexData + vDataIndex);
        GLfloat* tl = (*vertexData + vDataIndex + vertexesX * 3);
        GLfloat* lr = (*vertexData + vDataIndex + 3);
        GLfloat* tr = (*vertexData + vDataIndex + vertexesX * 3 + 3);
        // triangle 1 vertex 1
        triangleVertexData[i + 0 + 0] = ll[0];
        triangleVertexData[i + 0 + 1] = ll[1];
        triangleVertexData[i + 0 + 2] = ll[2];
        // triangle 1 vertex 2
        triangleVertexData[i + 3 + 0] = tl[0];
        triangleVertexData[i + 3 + 1] = tl[1];
        triangleVertexData[i + 3 + 2] = tl[2];
        // triangle 1 vertex 3
        triangleVertexData[i + 6 + 0] = tr[0];
        triangleVertexData[i + 6 + 1] = tr[1];
        triangleVertexData[i + 6 + 2] = tr[2];
        // triangle 2 vertex 4
        triangleVertexData[i + 9 + 0] = ll[0];
        triangleVertexData[i + 9 + 1] = ll[1];
        triangleVertexData[i + 9 + 2] = ll[2];
        // triangle 2 vertex 5
        triangleVertexData[i + 12 + 0] = tr[0];
        triangleVertexData[i + 12 + 1] = tr[1];
        triangleVertexData[i + 12 + 2] = tr[2];
        // triangle 2 vertex 6
        triangleVertexData[i + 15 + 0] = lr[0];
        triangleVertexData[i + 15 + 1] = lr[1];
        triangleVertexData[i + 15 + 2] = lr[2];
    }
    GLfloat* triangleTexCoordData;
    triangleTexCoordData = (GLfloat*)malloc(sizeof(GLfloat) * vertexesX * vertexesY * 2 * 6);
    for (int i = 0; i < vertexesX * vertexesY * 2 * 6; i += 2 * 6) {
        int x = (i / 12) % vertexesX;
        int y = (i / 12) / vertexesX;
        int vDataIndex = (int)(((double)i) * 1.5) / 6;
        if (x >= vertexesX - 1 || y >= vertexesY - 1) {
            GLfloat* ll = (*vertexData + vDataIndex);
            for (int j = 0; j < 6; ++j) {
                // This is probably broken
                triangleTexCoordData[i + j * 2 + 0] = ll[0];
                triangleTexCoordData[i + j * 2 + 1] = ll[2];
            }
            continue;
        }
        GLfloat* ll = (*vertexData + vDataIndex); // this indexing breaks
        GLfloat* tl = (*vertexData + vDataIndex + vertexesX * 2);
        GLfloat* lr = (*vertexData + vDataIndex + 2);
        GLfloat* tr = (*vertexData + vDataIndex + vertexesX * 2 + 2);
        // triangle 1 vertex 1
        triangleTexCoordData[i + 0 + 0] = ll[0];
        triangleTexCoordData[i + 0 + 1] = ll[1];
        // triangle 1 vertex 2
        triangleTexCoordData[i + 2 + 0] = tl[0];
        triangleTexCoordData[i + 2 + 1] = tl[1];
        // triangle 1 vertex 3
        triangleTexCoordData[i + 4 + 0] = tr[0];
        triangleTexCoordData[i + 4 + 1] = tr[1];
        // triangle 2 vertex 4
        triangleTexCoordData[i + 6 + 0] = ll[0];
        triangleTexCoordData[i + 6 + 1] = ll[1];
        // triangle 2 vertex 5
        triangleTexCoordData[i + 8 + 0] = tr[0];
        triangleTexCoordData[i + 8 + 1] = tr[1];
        // triangle 2 vertex 6
        triangleTexCoordData[i + 10 + 0] = lr[0];
        triangleTexCoordData[i + 10 + 1] = lr[1];
    }
    free(*vertexData);
    GLfloat* triangleNormalData;
    triangleNormalData = (GLfloat*)malloc(sizeof(GLfloat) * vertexesX * vertexesY * 3 * 6);
    for (int i = 0; i < vertexesX * vertexesY * 3 * 6 - 3 * 6; i += 3 * 6) {
        GLfloat normal[3];
        calculateNormal(normal, triangleVertexData + i, triangleVertexData + i + 3, triangleVertexData + i + 6);
        triangleNormalData[i + 0] = normal[0];
        triangleNormalData[i + 1] = normal[1];
        triangleNormalData[i + 2] = normal[2];
        triangleNormalData[i + 3] = normal[0];
        triangleNormalData[i + 4] = normal[1];
        triangleNormalData[i + 5] = normal[2];
        triangleNormalData[i + 6] = normal[0];
        triangleNormalData[i + 7] = normal[1];
        triangleNormalData[i + 8] = normal[2];
        triangleNormalData[i + 9] = normal[0];
        triangleNormalData[i + 10] = normal[1];
        triangleNormalData[i + 11] = normal[2];
        triangleNormalData[i + 12] = normal[0];
        triangleNormalData[i + 13] = normal[1];
        triangleNormalData[i + 14] = normal[2];
        triangleNormalData[i + 15] = normal[0];
        triangleNormalData[i + 16] = normal[1];
        triangleNormalData[i + 17] = normal[2];
    }
    *vertexData = triangleVertexData;
    *texCoordData = triangleTexCoordData;
    *normalData = triangleNormalData;
}

void free_vertexes(GLfloat* vertexData, GLfloat* normalData) {
    free(vertexData);
    free(normalData);
}
