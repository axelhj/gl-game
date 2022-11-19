#ifndef MAT4_H
#define MAT4_H

#include <cstdlib>
#include <math.h>

extern float* mat_create();

extern void mat_destroy(float* m);

extern float* mat_copy(float *m);

extern float* mat_copy_to(float *f, float *t);

extern float* mat_set_to(float * from, float* to);

//extern float* transpose();

extern float* mat_identity(float* m);

extern float* mat_scale(float* m, float x, float y, float z);

extern float* mat_rot_x(float* m, float t);

extern float* mat_rot_y(float* m, float t);

extern float* mat_rot_z(float* m, float t);

extern float* mat_rot_axis(float* m, float t, float x, float y, float z);

extern float* mat_translation(float* m, float x, float y, float z);

extern void mat_multiplicate(float* l, float* r, float* res);

extern float* mat_perspective(float* m, float fov, float n, float f);

//extern float* mat_vec_multiplicate(float* mat_l, float* vec_r, float* vec_res);

#endif /* MAT4_H */

