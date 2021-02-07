/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: axelhjelmqvist
 *
 * Created on den 12 januari 2017, 15:15
 */

#include <cstdlib>
#include <stdio.h>
#include <windows.h> // For sleep
//#include <time.h> // For nanosleep
#include "main.h"
#include "draw.h"
#include "sprite.h"

void millisleep(unsigned milliseconds) {
//    struct timespec timespec;
//    timespec.tv_sec = milliseconds / 1000;
//    timespec.tv_nsec = (milliseconds % 1000) * 1000000;
//    nanosleep(&timespec, NULL);
    Sleep(milliseconds);
}

static bool running = false;

static float pos[3] = {
    -0.495, 0.495, 0.198
};

void updateGl(DRAW_ENTITY* drawEntity, int* keys) {
    int l = keys[0];
    int r = keys[1];
    int u = keys[2];
    int d = keys[3];
    int a = keys[4];
    int b = keys[5];
    float rate = 3.0 * 0.0165;
    if (d) {
        pos[1] -= rate;
    } else if (u) {
        pos[1] += rate;
    }
    if (l) {
        pos[0] -= rate;
    } else if (r) {
        pos[0] += rate;
    }
    if (a) {
        pos[2] -= rate;
    } else if (b) {
        pos[2] += rate;
    }
    mat_scale(drawEntity->modelMat, 0.3, 0.3, 0.3);
    GLfloat* intermediate = (float*)malloc(sizeof(float)*16);
    // Pass 0
    mat_rot_x(intermediate, 3.1415);
    GLfloat* modelMatCopy = mat_copy(drawEntity->modelMat);
    mat_multiplicate(modelMatCopy, intermediate, drawEntity->modelMat);
    // Pass 1
    mat_rot_y(intermediate, 3.1415f / 4.0f);
    modelMatCopy = mat_copy(drawEntity->modelMat);
    mat_multiplicate(modelMatCopy, intermediate, drawEntity->modelMat);
    // Pass 2
    mat_translation(intermediate, pos[0], pos[1], pos[2]);
    mat_set_to(modelMatCopy, drawEntity->modelMat);
    mat_multiplicate(modelMatCopy, intermediate, drawEntity->modelMat);

    mat_destroy(modelMatCopy);
    mat_destroy(intermediate);
}

#define WINDOW_WIDTH 1200

#define WINDOW_HEIGHT 900

static SPRITE* entities[5] = { 0, 0, 0, 0, 0 };

/*
 * GLFW main
 */
int main(int argc, char** argv) {
    running = initGl("Demo GL", WINDOW_WIDTH, WINDOW_HEIGHT);
    running = running && create_sprite(entities + 0, "game-hero.png");
    running = running && create_sprite(entities + 1, "game-hero.png");
    running = running && create_sprite(entities + 2, "game-hero.png");
    running = running && create_sprite(entities + 3, "game-hero.png");
    running = running && create_sprite(entities + 4, "ground.png");
    mat_translation((*(entities + 0))->draw_entity->modelMat, 0.1f, 0, 0);
    mat_translation((*(entities + 1))->draw_entity->viewMat, 1.0f, 0, 0);
    mat_translation((*(entities + 2))->draw_entity->viewMat, 2.0f, 0, 0);
    mat_translation((*(entities + 3))->draw_entity->viewMat, -1.0f, 0, 0);
    mat_translation((*(entities + 4))->draw_entity->modelMat, 0.495, 0.495, 0.198);
    GLfloat* intermediate = (float*)malloc(sizeof(float)*16);
    mat_rot_x(intermediate, 3.1415f / 2.0f);
    GLfloat* modelMatCopy = mat_copy((*(entities + 4))->draw_entity->modelMat);
    mat_multiplicate(modelMatCopy, intermediate, (*(entities + 4))->draw_entity->modelMat);
    mat_destroy(modelMatCopy);
    mat_destroy(intermediate);

    if (!running) {
        printf("Loading failed");
        terminateGl();
        return -1;
    }
    while (running) {
        updateGl((*(entities + 0))->draw_entity, keys);
        updateGl((*(entities + 1))->draw_entity, keys);
        updateGl((*(entities + 2))->draw_entity, keys);
        updateGl((*(entities + 3))->draw_entity, keys);
        running = !keys[6];
        preDraw();
        drawGl((*(entities + 0))->draw_entity);
        drawGl((*(entities + 1))->draw_entity);
        drawGl((*(entities + 2))->draw_entity);
        drawGl((*(entities + 3))->draw_entity);
        drawGl((*(entities + 4))->draw_entity);
        running = running && postDraw();
        if (running) {
            millisleep(16); // not required as glfwSwapBuffers is blocking
        }
    }
    terminateGl();
    return 0;
}
