# Gl-game with C++ & GLFW

Experimental OpenGl-engine with collision-resolution and a "typewriter style" text renderer and a weird protagonist. Supports 3D.

## In progress

- Dynamic shaders (basically allow templating and using a dynamic structure to set uniforms & maybe attributes.
- Improve collissions to allow non-axis-aligned resolutions and shapes besides boxes.
- Do something with the MSPaint generated assets.
- Title-screen, levels, monsters, credits, options-screen, gfx-settings
- Integrate SDL for sound & better text rendering.

## Finished

- Implemented a-star algorithm in C (maybe it has a class).
- Refactor C-style code to use smart pointers & C++ classes.
- Resolve collissions between multiple object (AABB-style shapes).
- A mesh generator that uses a bitmap as the heightmap to produce a uniform "grid" or terrain (not optimized).
- Captures the mouse and points the camera in relation to events.
- Switched from CodeBlocks project to CMake with g++. Hard codes some compiler paths for Msys2 on Windows and specifies various compiler-flags and linker options explicitly which is not best practice for CMake or build tools in general. Committed-in build artefacts for dependencies which obviously would only work on windows.
- Clangd (LSP server) support with G++ on Windows with compile_commands.json.

# To run

## To clean buildsystem & artefacts

Run `rmdir /s /q build`

## Make a fresh build (generate MSYS makefiles) - Mingw should be installed (if using Windows):

Run `cmake -B ./build -G "MSYS Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1
&&cmake --build build`

(CMAKE_EXPORT_COMPILE_COMMANDS causes the compile_commands.json to be generated which is used by clangd to understand what compiler commands and source/header files are included in the build for LSP support.)
