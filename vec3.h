#ifndef VEC3_H
#define VEC3_H
#include <math.h>

extern float* vec_3_copy(float* to, float* from);

extern float* vec_3_normalize(float* vec3);

extern float* vec_3_cross(float* res, float* vec_a, float* vec_b);

extern float vec_3_angle_between(float* vec_l, float* vec_r);

extern float* vec_3_normal_to(float* res, float* vec);

extern float vec_3_component_scalar(float* vec, float* vec_dir);

extern float* vec_3_component(float* res, float* vec, float* vec_dir);

extern float vec_3_dot(float* vec);

extern float* vec_3_reflect(float* res, float* vec, float* normal);

extern float vec_3_length(float* vec);

extern float* vec_3_mul(float* res, float* vec_l, float* vec_r);

extern float* vec_3_mul_scalar(float* res, float* vec, float value);

extern float* vec_3_div_scalar(float* res, float* vec, float value);

extern float* vec_3_add(float* res, float* vec_l, float* vec_r);

extern float* vec_3_sub(float* res, float* vec_l, float* vec_r);

#endif // VEC3_H
