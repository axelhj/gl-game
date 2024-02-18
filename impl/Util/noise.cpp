#include "impl/Util/noise.h"

static int permutations[] = {
    151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140,
    36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120,
    234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33, 
    88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71,
    134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133,
    230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161,
    1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130,
    116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250,
    124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227,
    47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44,
    154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98,
    108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251, 34,
    242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14,
    239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121,
    50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243,
    141, 128, 195, 78, 66, 215, 61, 156, 180
};

static int p[512];

static float lerp(float min, float max, float val) {
    return min + (max - min) * val;
}

static float fade(float t) {
    float t2 = t * t;
    float t3 = t * t * t;
    return 6 * t2 * t3 + 15 * t2 * t2 - 10 * t3;
}

static bool p_inited = false;

static float grad_ind(int hash, float x, float y, float z) {
    hash = hash & 15;
    float u = (hash < 8) ? x : y;
    float v = (hash < 4) ? y :
        (hash == 12 || hash == 14) ? x :
        z;
    return (hash & 1) == 0 ? u : -u + (hash & 2) == 0 ? v : -v;
}

float perlin(float x, float y, float z) {
    if (!p_inited) {
        for (int i = 0; i < 512; ++i) {
            p[i] = (i < 256) ? permutations[i] : permutations[i - 256];
        }
        p_inited = true;
    }
    int unit_cube[3] = {(int)x & 255, (int)y & 255, (int)z & 255}; //i
    float location[3] = {x - (int)x, y - (int)y, z - (int)z}; //f
    float eased_location[3] = {fade(location[0]), fade(location[1]), fade(location[2])};
    int a1 = p[p[p[unit_cube[0]]     + unit_cube[1]]     + unit_cube[2]],
    a2 = p[p[p[    unit_cube[0]]     + unit_cube[1] + 1] + unit_cube[2]],
    a3 = p[p[p[    unit_cube[0]]     + unit_cube[1]]     + unit_cube[2] + 1],
    a4 = p[p[p[    unit_cube[0]]     + unit_cube[1] + 1] + unit_cube[2] + 1],
    a5 = p[p[p[    unit_cube[0] + 1] + unit_cube[1]]     + unit_cube[2]],
    a6 = p[p[p[    unit_cube[0] + 1] + unit_cube[1] + 1] + unit_cube[2]],
    a7 = p[p[p[    unit_cube[0] + 1] + unit_cube[1]]     + unit_cube[2] + 1],
    a8 = p[p[p[    unit_cube[0] + 1] + unit_cube[1] + 1] + unit_cube[2] + 1];
    float x1 = lerp(grad_ind(a1, location[0]       , location[1]       , location[2]),
                    grad_ind(a5, location[0] - 1.0f, location[1]       , location[2]), eased_location[0]);
    float x2 = lerp(grad_ind(a2, location[0]       , location[1] - 1.0f, location[2]),
                    grad_ind(a6, location[0] - 1.0f, location[1] - 1.0f, location[2]), eased_location[0]);
    float y1 = lerp(x1, x2, eased_location[1]);
    x1 = lerp(grad_ind(a3, location[0]       , location[1]       , location[2] - 1.0f),
              grad_ind(a7, location[0] - 1.0f, location[1]       , location[2] - 1.0f), eased_location[0]);
    x2 = lerp(grad_ind(a4, location[0]       , location[1] - 1.0f, location[2] - 1.0f),
              grad_ind(a8, location[0] - 1.0f, location[1] - 1.0f, location[2] - 1.0f), eased_location[0]);
    float y2 = lerp(x1, x2, eased_location[1]);
    return (lerp(y1, y2, eased_location[2]) + 1.0f) / 2.0f;
}
