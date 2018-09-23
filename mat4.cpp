#include "mat4.h"

float* mat_create() {
    return mat_identity((float*)malloc(sizeof(float) * 16));
}

void mat_destroy(float* m) {
    free(m);
}

float* mat_copy(float *m) {
    float* copy = (float*)malloc(sizeof(float) * 16);
    copy[0] = m[0]; copy[1] = m[1]; copy[2] = m[2]; copy[3] = m[3]; 
    copy[4] = m[4]; copy[5] = m[5]; copy[6] = m[6]; copy[7] = m[7]; 
    copy[8] = m[8]; copy[9] = m[9]; copy[10] = m[10]; copy[11] = m[11]; 
    copy[12] = m[12]; copy[13] = m[13]; copy[14] = m[14]; copy[15] = m[15];
    return copy;
}

float* mat_set_to(float * from, float* to) {
    to[0]  = from[0];  to[1]  = from[1];  to[2]  = from[2];  to[3]  = from[3]; 
    to[4]  = from[4];  to[5]  = from[5];  to[6]  = from[6];  to[7]  = from[7]; 
    to[8]  = from[8];  to[9]  = from[9];  to[10] = from[10]; to[11] = from[11]; 
    to[12] = from[12]; to[13] = from[13]; to[14] = from[14]; to[15] = from[15];
    return to;
}

//float* transpose() {
//    float[] m = data;
//    /*m[0]  = m[0];*/ m[1]  = m[4];   m[2]  = m[8];    m[3]  = m[12]; 
//      m[4]  = m[1]; /*m[5]  = m[5];*/ m[6]  = m[9];    m[7]  = m[13]; 
//      m[8]  = m[2];   m[9]  = m[6]; /*m[10] = m[10];*/ m[11] = m[14]; 
//      m[12] = m[3];   m[13] = m[7];   m[14] = m[11]; /*m[15] = m[15];*/
//    return this;
//}

float* mat_identity(float* m) {
    m[0]  = 1.0f; m[1]  = 0.0f; m[2]  = 0.0f; m[3]  = 0.0f; 
    m[4]  = 0.0f; m[5]  = 1.0f; m[6]  = 0.0f; m[7]  = 0.0f; 
    m[8]  = 0.0f; m[9]  = 0.0f; m[10] = 1.0f; m[11] = 0.0f; 
    m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
    return m;
}

float* mat_scale(float* m, float x, float y, float z) {
    m[0]  = x;    m[1]  = 0.0f; m[2]  = 0.0f; m[3]  = 0.0f; 
    m[4]  = 0.0f; m[5]  = y;    m[6]  = 0.0f; m[7]  = 0.0f; 
    m[8]  = 0.0f; m[9]  = 0.0f; m[10] = z;    m[11] = 0.0f; 
    m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
    return m;
}

float* mat_rot_x(float* m, float t) {
    m[0]  = 1.0f; m[1]  = 0.0f;   m[2]  = 0.0f;   m[3]  = 0.0f;
    m[4]  = 0.0f; m[5]  = cos(t); m[6]  =-sin(t); m[7]  = 0.0f;
    m[8]  = 0.0f; m[9]  = sin(t); m[10] = cos(t); m[11] = 0.0f;
    m[12] = 0.0f; m[13] = 0.0f;   m[14] = 0.0f;   m[15] = 1.0f;
    return m;
}

float* mat_rot_y(float* m, float t) {
    m[0]  = cos(t); m[1]  = 0.0f; m[2]  = -sin(t); m[3]  = 0.0f; 
    m[4]  = 0.0f;   m[5]  = 1.0f; m[6]  = 0.0f;   m[7]  = 0.0f; 
    m[8]  = sin(t); m[9]  = 0.0f; m[10] = cos(t); m[11] = 0.0f; 
    m[12] = 0.0f;   m[13] = 0.0f; m[14] = 0.0f;   m[15] = 1.0f;
    return m;
}

float* mat_rot_z(float* m, float t) {
    m[0]  = cos(t); m[1]  =-sin(t); m[2]  = 0.0f; m[3]  = 0.0f; 
    m[4]  = sin(t); m[5]  = cos(t); m[6]  = 0.0f; m[7]  = 0.0f; 
    m[8]  = 0.0f;   m[9]  = 0.0f;   m[10] = 1.0f; m[11] = 0.0f; 
    m[12] = 0.0f;   m[13] = 0.0f;   m[14] = 0.0f; m[15] = 1.0f;
    return m;
}

float* mat_rot_axis(float* m, float t, float x, float y, float z) {
    float s = sin(t), c = cos(t), xx = x*x;
    float xy = x*y, sz = s*z, xz = x*z, sy = s*y;
    float yy = y*y, yz = y*z, sx = s*x, zz = z*z;
    m[0]=c+(1.0f-c)*xx;  m[1]=(1.0f-c)*xy+sz; m[2]=(1.0f-c)*xz-sy; m[3]= 0;
    m[4]=(1.0f-c)*xy-sz; m[5]=c+(1.0f-c)*yy;  m[6]=(1.0f-c)*yz+sx; m[7]= 0;
    m[8]=(1.0f-c)*xz+sy; m[9]=(1.0f-c)*yz-sx; m[10]=c+(1.0f-c)*zz; m[11]=0;
    m[12]=0;             m[13]=0;             m[14]=0;             m[15]=1;
    return m;
}

float* mat_translation(float* m, float x, float y, float z) {
    m[0]  = 1.0f; m[1]  = 0.0f; m[2]  = 0.0f; m[3]  = x;
    m[4]  = 0.0f; m[5]  = 1.0f; m[6]  = 0.0f; m[7]  = y;
    m[8]  = 0.0f; m[9]  = 0.0f; m[10] = 1.0f; m[11] = z;
    m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
    return m;
}

void mat_multiplicate(float* l, float* r, float* res) {
    int i, j, k;
    float sum;
    for (i = 0 ; i < 4; ++i) { //row
        for (j = 0; j < 4; ++j) { //column
            sum = 0.0f;
            for (k = 0; k < 4; ++k) { //current matrix index
                sum += l[i + k * 4] * r[k + j * 4];
            }
            res[i + j * 4] = sum;
        }
    }
}

float* mat_perspective(float* m, float fov, float n, float f) {
    float ratio = 1.0f / (800.0f / 600.0f);
    float projX = (float)tan((double)(fov / 2.0f));
    float projY = 1.0f / ratio * (float)tan((double)(fov / 2.0f));
    m[0] = projX; m[1]  = 0;     m[2]  = 0;            m[3]  = 0;
    m[4] = 0;     m[5]  = projY; m[6]  = 0;            m[7]  = 0;
    m[8] = 0;     m[9]  = 0;     m[10] = -(f+n)/(n-f); m[11] = (2.0f*f*n)/(n-f);
    m[12] = 0;    m[13] = 0;     m[14] = 1.0f;         m[15] = 0;
    return m;
}

//static float* mat_vec_multiplicate(float* mat_l, float* vec_r, float* vec_res) {
//    float* l = mat_l;
//    float* r = vec_r;
//    r.x = l[0] * r.x + l[1] * r.y + l[2] * r.z + l[3] * r.w;
//    r.y = l[4] * r.x + l[5] * r.y + l[6] * r.z + l[7] * r.w;
//    r.z = l[8] * r.x + l[9] * r.y + l[10]* r.z + l[11]* r.w;
//    r.w = l[12]* r.x + l[13]* r.y + l[14]* r.z + l[15]* r.w;
//}
