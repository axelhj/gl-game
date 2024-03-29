#include <stdio.h>
#include <windows.h> // For sleep
//#include <time.h> // For nanosleep
#include "impl/main.h"
#include "impl/Game/start.h"
#include "impl/Util/unbuffered.h"
#include "impl/Util/glfw_helper.h"

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
    Start* level_instance = new Start();
    if (!running) {
        printf("Loading failed");
        terminate_gl();
        return -1;
    }
    float time = 0;
    while (running) {
        level_instance->update(keys, 0.0165f, time);
        time += 0.0165f;
        running = !keys[6];
        pre_draw();
        level_instance->draw();
        running = running && post_draw();
        if (running) {
            millisleep(4); // not required as glfwSwapBuffers is blocking
        }
    }
    delete level_instance;
    terminate_gl();
    return 0;
}
