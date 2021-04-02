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
#include "level.h"

void millisleep(unsigned milliseconds) {
//    struct timespec timespec;
//    timespec.tv_sec = milliseconds / 1000;
//    timespec.tv_nsec = (milliseconds % 1000) * 1000000;
//    nanosleep(&timespec, NULL);
    Sleep(milliseconds);
}

static bool running = false;

#define WINDOW_WIDTH 1200

#define WINDOW_HEIGHT 900

/*
 * GLFW main
 */
int main(int argc, char** argv) {
    running = init_gl("Demo GL", WINDOW_WIDTH, WINDOW_HEIGHT);
    running = running && init_level();
    if (!running) {
        printf("Loading failed");
        terminate_gl();
        return -1;
    }
    float time = 0;
    while (running) {
        update_level(keys, 0.0165f, time);
        time += 0.0165f;
        running = !keys[6];
        pre_draw();
        draw_level();
        running = running && post_draw();
        if (running) {
            millisleep(4); // not required as glfwSwapBuffers is blocking
        }
    }
    destroy_level();
    terminate_gl();
    GetChWin();
    return 0;
}
