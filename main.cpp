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

void updateGl(GAME_ENTITY* gameEntity, int* keys) {
    int l = keys[0];
    int r = keys[1];
    int u = keys[2];
    int d = keys[3];
    int a = keys[4];
    int b = keys[5];
    float rate = 3.0 * 0.0165;
    if (u) {
        pos[0] += rate;
    } else if (d) {
        pos[0] -= rate;
    }
    if (l) {
        pos[1] += rate;
    } else if (r) {
        pos[1] -= rate;
    }
    if (a) {
        pos[2] += rate;
    } else if (b) {
        pos[2] -= rate;
    }
    mat_scale(gameEntity->modelMat, 0.3, 0.3, 0.3);
    GLfloat* intermediate = (float*)malloc(sizeof(float)*16);
    // Pass 0
    mat_rot_x(intermediate, 3.1415);
    GLfloat* modelMatCopy = mat_copy(gameEntity->modelMat);
    mat_multiplicate(modelMatCopy, intermediate, gameEntity->modelMat);
    // Pass 1
    mat_rot_y(intermediate, 3.1415f / 4.0f);
    modelMatCopy = mat_copy(gameEntity->modelMat);
    mat_multiplicate(modelMatCopy, intermediate, gameEntity->modelMat);
    // Pass 2
    mat_translation(intermediate, pos[0], pos[1], pos[2]);
    mat_set_to(modelMatCopy, gameEntity->modelMat);
    mat_multiplicate(modelMatCopy, intermediate, gameEntity->modelMat);

    mat_destroy(modelMatCopy);
    mat_destroy(intermediate);
}

#define WINDOW_WIDTH 1200

#define WINDOW_HEIGHT 900

static GAME_ENTITY entities[2] = { 0, 0 };

/*
 * GLFW main
 */
int main(int argc, char** argv) {
    printf("Main");
    running = initGl("Demo GL", WINDOW_WIDTH, WINDOW_HEIGHT);
    setSquareVertexData(entities + 0);
    setSquareVertexData(entities + 1);
    running = running &&
        loadGl(entities + 0) && loadGlTexture(entities + 0, "game-hero.png") &&
        loadGl(entities + 1) && loadGlTexture(entities + 1, "ground.png");
    mat_translation((entities + 1)->modelMat, -0.495, 0.495, 0.198);
    GLfloat* intermediate = (float*)malloc(sizeof(float)*16);
    mat_rot_x(intermediate, 3.1415f / 2.0f);
    GLfloat* modelMatCopy = mat_copy((entities + 1)->modelMat);
    mat_multiplicate(modelMatCopy, intermediate, (entities + 1)->modelMat);
    mat_destroy(modelMatCopy);
    mat_destroy(intermediate);

    if (!running) {
        printf("Loading failed");
        terminateGl();
        return -1;
    }
    while (running) {
        updateGl(entities + 0, keys);
        running = !keys[6];
        preDraw();
        drawGl(entities + 0);
        drawGl(entities + 1);
        running = running && postDraw();
        if (running) {
            millisleep(16); // not required as glfwSwapBuffers is blocking
        }
    }
    terminateGl();
    return 0;
}
