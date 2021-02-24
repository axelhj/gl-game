#include "vec3.h"

float* vec_3_normalize(float* vec3)
{
    float vec_length = vec_3_length(vec3);
    if (vec_length == 0.0f) {
        return vec3;
    }
    vec3[0] /= vec_length;
    vec3[1] /= vec_length;
    vec3[2] /= vec_length;
    return vec3;
}

float* vec_3_cross(float* res, float* vec_a, float* vec_b)
{
    res[0] = vec_a[1] * vec_b[2] - vec_a[2] * vec_b[1];
    res[1] = vec_a[2] * vec_b[0] - vec_a[0] * vec_b[2];
    res[2] = vec_a[0] * vec_b[1] - vec_a[1] * vec_b[0];
    return res;
}

float vec_3_angle_between(float* vec_l, float* vec_r)
{
    float vec_diff[3];
    vec_3_sub(vec_diff, vec_r, vec_l);
    float m1 = vec_3_length(vec_l);
    float m2 = vec_3_length(vec_r);
    float m3 = vec_3_length(vec_diff);
//    if (m1 == 0.0f || m2 == 0.0f) {
//        error!
//    }
    if (m3 == 0.0f) {
        return 0; // Equal vectors.
    }
    return (float)acos((m2 * m2 + m1 * m1 - m3 * m3) / (2.0f * m1 * m2));
}

float* vec_3_normal_to(float* res, float* vec)
{
    // return vector(-vector[2], vector);
    res[0] = -vec[2];
    res[1] = vec[0];
    res[2] = vec[1];
    return res;
}

float vec_3_component_scalar(float* vec, float* vec_dir)
{
  // TODOFIX: Does not actually do vec3.
  float alpha = atan2(vec_dir[1], vec_dir[0]);
  float theta = atan2(vec[1], vec[0]);
  return vec_3_length(vec) * (float)cos(theta - alpha);
}

float* vec_3_component(float* res, float* vec, float* vec_dir)
{
    float vec_unit_length[3];
    vec_unit_length[0] = vec_dir[0];
    vec_unit_length[1] = vec_dir[1];
    vec_unit_length[2] = vec_dir[2];
    vec_3_mul_scalar(vec_unit_length, vec_unit_length, 1.0f / vec_3_length(vec_dir));
    return vec_3_mul_scalar(
        res,
        vec_unit_length,
        vec_3_component_scalar(vec, vec_dir)
    );
}

float vec_3_dot(float* vec_l, float* vec_r)
{
    return vec_l[0] * vec_r[0] + vec_l[1] * vec_r[1] + vec_l[2] * vec_r[2];
}

float* vec_3_reflect(float* res, float* vec, float* normal)
{
  vec_3_mul_scalar(res, normal, 2.0f * vec_3_dot(vec, normal));
  return vec_3_sub(res, vec, res);
}

float vec_3_length(float* vec)
{
    float x = vec[0] * vec[0];
    float y = vec[1] * vec[1];
    float z = vec[2] * vec[2];
    return (float)sqrt(x + y + z);
}

float* vec_3_mul(float* res, float* vec_l, float* vec_r)
{
    res[0] = vec_l[0] * vec_r[0];
    res[1] = vec_l[1] * vec_r[1];
    res[2] = vec_l[2] * vec_r[2];
    return res;
}

float* vec_3_mul_scalar(float* res, float* vec, float value)
{
    res[0] = vec[0] * value;
    res[1] = vec[1] * value;
    res[2] = vec[2] * value;
    return res;
}

float* vec_3_div_scalar(float* res, float* vec, float value)
{
    float mul = 1.0f / value;
    res[0] = vec[0] * mul;
    res[1] = vec[1] * mul;
    res[2] = vec[2] * mul;
    return res;
}

float* vec_3_add(float* res, float* vec_l, float* vec_r)
{
    res[0] = vec_l[0] + vec_r[0];
    res[1] = vec_l[1] + vec_r[1];
    res[2] = vec_l[2] + vec_r[2];
    return res;
}

float* vec_3_sub(float* res, float* vec_l, float* vec_r)
{
    res[0] = vec_l[0] - vec_r[0];
    res[1] = vec_l[1] - vec_r[1];
    res[2] = vec_l[2] - vec_r[2];
    return res;
}
