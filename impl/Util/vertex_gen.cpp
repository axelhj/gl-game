#include "impl/Util/vertex_gen.h"

#define STB_IMAGE_IMPLEMENTATION
#include "deps/stb_image.h"

#include "impl/Util/vec3.h"

unsigned char* get_image_data(const char* file_name, int* image_width, int* image_height) {
    int x, y, components_per_pixel;
    unsigned char* data = stbi_load(file_name, &x, &y, &components_per_pixel, 4);
    /*ignore since components will correspond to 5th argument of stbi_load function
    if (components_per_pixel != 4) {
        return NULL;
    }*/
    *image_width = x;
    *image_height = y;
    return data;
}

void delete_image_data(unsigned char* image_data) {
    stbi_image_free(image_data);
}

static void calculate_normal(GLfloat* normal, GLfloat* vertex_a, GLfloat* vertex_b, GLfloat* vertex_c) {
    GLfloat temp_vec[9];
    vec_3_cross(normal, vec_3_sub(temp_vec + 3, vertex_b, vertex_a), vec_3_sub(temp_vec + 6, vertex_c, vertex_a));
    vec_3_normalize(normal);
}

static float get_height_val(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    return ((float)r / 255.0f) * ((float)g / 255.0f) * (255.0f / (float)b);
}

void generate_vertexes(GLfloat** vertex_data, GLfloat** tex_coord_data, GLfloat** normal_data,
        unsigned char* image_data, int image_width, int image_height, int vertexes_x, int vertexes_y
) {
    *vertex_data = (GLfloat*)malloc(sizeof(GLfloat) * vertexes_x * vertexes_y* 3);
    float triangle_width = ((float)image_width) / ((float)vertexes_x);
    float triangle_height = ((float)image_height) / ((float)vertexes_y);
    for (int i = 0; i < vertexes_x * vertexes_y * 3; i += 3) {
        float x = (i / 3) % vertexes_x;
        float y = (i / 3) / vertexes_x;
        int image_pixel_index = ((int)(x * triangle_width) + ((int)(y * triangle_height)) * image_width) * 4;
        if (image_pixel_index >= image_width * image_height * 4 - 4) {
            image_pixel_index = image_width * image_height * 4 - 4 - 1;
        }
        float v_height = get_height_val(
            image_data[image_pixel_index + 0],
            image_data[image_pixel_index + 1],
            image_data[image_pixel_index + 2],
            image_data[image_pixel_index + 3]
        );/**/
        /*float scaled_x = (x) / ((float)vertexes_x * 0.5f);
        float scaled_y = (y) / ((float)vertexes_x * 0.5f);
        float v_height = perlin(scaled_x, scaled_y, 0);
        printf("%f %f\n", y, scaled_y);
        */
         //vHeight = vHeight * 0.05f + 0.5f;
        (*vertex_data)[i + 0] = (GLfloat)(x / (float)vertexes_x);
        (*vertex_data)[i + 1] = (GLfloat)v_height;
        (*vertex_data)[i + 2] = (GLfloat)(y / (float)vertexes_y);
    }
    GLfloat* triangle_vertex_data;
    triangle_vertex_data = (GLfloat*)malloc(sizeof(GLfloat) * vertexes_x * vertexes_y * 3 * 6);
    for (int i = 0; i < vertexes_x * vertexes_y * 3 * 6; i += 3 * 6) {
        int x = (i / 18) % vertexes_x;
        int y = (i / 18) / vertexes_x;
        int v_data_index = i / 6;
        if (x >= vertexes_x - 1 || y >= vertexes_y - 1) {
            GLfloat* ll = (*vertex_data + v_data_index);
            for (int j = 0; j < 6; ++j) {
                triangle_vertex_data[i + j * 3 + 0] = ll[0];
                triangle_vertex_data[i + j * 3 + 1] = ll[1];
                triangle_vertex_data[i + j * 3 + 2] = ll[2];
            }
            continue;
        }
        GLfloat* ll = (*vertex_data + v_data_index);
        GLfloat* tl = (*vertex_data + v_data_index + vertexes_x * 3);
        GLfloat* lr = (*vertex_data + v_data_index + 3);
        GLfloat* tr = (*vertex_data + v_data_index + vertexes_x * 3 + 3);
        // triangle 1 vertex 1
        triangle_vertex_data[i + 0 + 0] = ll[0];
        triangle_vertex_data[i + 0 + 1] = ll[1];
        triangle_vertex_data[i + 0 + 2] = ll[2];
        // triangle 1 vertex 2
        triangle_vertex_data[i + 3 + 0] = tl[0];
        triangle_vertex_data[i + 3 + 1] = tl[1];
        triangle_vertex_data[i + 3 + 2] = tl[2];
        // triangle 1 vertex 3
        triangle_vertex_data[i + 6 + 0] = tr[0];
        triangle_vertex_data[i + 6 + 1] = tr[1];
        triangle_vertex_data[i + 6 + 2] = tr[2];
        // triangle 2 vertex 4
        triangle_vertex_data[i + 9 + 0] = ll[0];
        triangle_vertex_data[i + 9 + 1] = ll[1];
        triangle_vertex_data[i + 9 + 2] = ll[2];
        // triangle 2 vertex 5
        triangle_vertex_data[i + 12 + 0] = tr[0];
        triangle_vertex_data[i + 12 + 1] = tr[1];
        triangle_vertex_data[i + 12 + 2] = tr[2];
        // triangle 2 vertex 6
        triangle_vertex_data[i + 15 + 0] = lr[0];
        triangle_vertex_data[i + 15 + 1] = lr[1];
        triangle_vertex_data[i + 15 + 2] = lr[2];
    }
    GLfloat* triangle_tex_coord_data;
    triangle_tex_coord_data = (GLfloat*)malloc(sizeof(GLfloat) * vertexes_x * vertexes_y * 2 * 6);
    for (int i = 0; i < vertexes_x * vertexes_y * 2 * 6; i += 2 * 6) {
        int x = (i / 12) % vertexes_x;
        int y = (i / 12) / vertexes_x;
        int v_data_index = (int)(((double)i) * 1.5) / 6;
        if (x >= vertexes_x - 1 || y >= vertexes_y - 1) {
            GLfloat* ll = (*vertex_data + v_data_index);
            for (int j = 0; j < 6; ++j) {
                // This is probably broken
                triangle_tex_coord_data[i + j * 2 + 0] = ll[0];
                triangle_tex_coord_data[i + j * 2 + 1] = ll[2];
            }
            continue;
        }
        GLfloat* ll = (*vertex_data + v_data_index); // this indexing breaks
        GLfloat* tl = (*vertex_data + v_data_index + vertexes_x * 2);
        GLfloat* lr = (*vertex_data + v_data_index + 2);
        GLfloat* tr = (*vertex_data + v_data_index + vertexes_x * 2 + 2);
        // triangle 1 vertex 1
        triangle_tex_coord_data[i + 0 + 0] = ll[0];
        triangle_tex_coord_data[i + 0 + 1] = ll[1];
        // triangle 1 vertex 2
        triangle_tex_coord_data[i + 2 + 0] = tl[0];
        triangle_tex_coord_data[i + 2 + 1] = tl[1];
        // triangle 1 vertex 3
        triangle_tex_coord_data[i + 4 + 0] = tr[0];
        triangle_tex_coord_data[i + 4 + 1] = tr[1];
        // triangle 2 vertex 4
        triangle_tex_coord_data[i + 6 + 0] = ll[0];
        triangle_tex_coord_data[i + 6 + 1] = ll[1];
        // triangle 2 vertex 5
        triangle_tex_coord_data[i + 8 + 0] = tr[0];
        triangle_tex_coord_data[i + 8 + 1] = tr[1];
        // triangle 2 vertex 6
        triangle_tex_coord_data[i + 10 + 0] = lr[0];
        triangle_tex_coord_data[i + 10 + 1] = lr[1];
    }
    free(*vertex_data);
    GLfloat* triangle_normal_data;
    triangle_normal_data = (GLfloat*)malloc(sizeof(GLfloat) * vertexes_x * vertexes_y * 3 * 6);
    for (int i = 0; i < vertexes_x * vertexes_y * 3 * 6 - 3 * 6; i += 3 * 6) {
        GLfloat normal[3];
        calculate_normal(normal, triangle_vertex_data + i, triangle_vertex_data + i + 3, triangle_vertex_data + i + 6);
        triangle_normal_data[i + 0] = normal[0];
        triangle_normal_data[i + 1] = normal[1];
        triangle_normal_data[i + 2] = normal[2];
        triangle_normal_data[i + 3] = normal[0];
        triangle_normal_data[i + 4] = normal[1];
        triangle_normal_data[i + 5] = normal[2];
        triangle_normal_data[i + 6] = normal[0];
        triangle_normal_data[i + 7] = normal[1];
        triangle_normal_data[i + 8] = normal[2];
        triangle_normal_data[i + 9] = normal[0];
        triangle_normal_data[i + 10] = normal[1];
        triangle_normal_data[i + 11] = normal[2];
        triangle_normal_data[i + 12] = normal[0];
        triangle_normal_data[i + 13] = normal[1];
        triangle_normal_data[i + 14] = normal[2];
        triangle_normal_data[i + 15] = normal[0];
        triangle_normal_data[i + 16] = normal[1];
        triangle_normal_data[i + 17] = normal[2];
    }
    *vertex_data = triangle_vertex_data;
    *tex_coord_data = triangle_tex_coord_data;
    *normal_data = triangle_normal_data;
}

void free_vertexes(GLfloat* vertex_data, GLfloat* normal_data) {
    free(vertex_data);
    free(normal_data);
}
