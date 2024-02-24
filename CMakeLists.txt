cmake_minimum_required(VERSION 3.21)

project(gl-game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-fexec-charset=850")

set(CMAKE_CXX_FLAGS "-I${PROJECT_SOURCE_DIR}")
set(CMAKE_CXX_FLAGS "-I${PROJECT_SOURCE_DIR}/deps/glew-2.1.0/include")
set(CMAKE_CXX_FLAGS "-I${PROJECT_SOURCE_DIR}/deps/glfw-3.3.9.bin.WIN64/include")
set(CMAKE_CXX_FLAGS "-I${PROJECT_SOURCE_DIR}/deps/glfw-3.3.9.bin.WIN64/include")
set(CMAKE_CXX_FLAGS "-I${PROJECT_SOURCE_DIR}/deps/libsrt-cebf7ca/src")

file(GLOB_RECURSE headers RELATIVE ${PROJECT_SOURCE_DIR} impl/**/*.h impl/*.h)
file(GLOB_RECURSE sources RELATIVE ${PROJECT_SOURCE_DIR} impl/**/*.cpp impl/*.cpp)

add_executable("gl-game" ${sources})
target_include_directories("gl-game" INTERFACE ${PROJECT_SOURCE_DIR})
target_sources("gl-game" PRIVATE FILE_SET headers BASE_DIRS TYPE HEADERS)

include(CMakePrintHelpers)
# cmake_print_variables(headers)

# GLORIOUS GLEW
add_library("glew" STATIC IMPORTED)
target_include_directories("glew" INTERFACE "deps/glew-2.1.0/include")
set_target_properties(
        "glew"
        PROPERTIES IMPORTED_LOCATION
        ${PROJECT_SOURCE_DIR}/deps/glew-2.1.0/lib/libglew32.a
)

# SPLENDID GLFW
add_library("glfw" STATIC IMPORTED)
target_include_directories("glfw" INTERFACE deps/glfw-3.3.9.bin.WIN64/include)
set_target_properties(
        "glfw"
        PROPERTIES IMPORTED_LOCATION
        ${PROJECT_SOURCE_DIR}/deps/glfw-3.3.9.bin.WIN64/lib-mingw-w64/libglfw3.a
)

# EXCELLENTE LIBRSRT
add_library("libsrt" STATIC IMPORTED)
target_include_directories("libsrt" INTERFACE deps/libsrt-cebf7ca/src)
set_target_properties(
        "libsrt"
        PROPERTIES IMPORTED_LOCATION
        ${PROJECT_SOURCE_DIR}/deps/libsrt-cebf7ca/libsrt.a
)

# AMAZING STB
add_library("stb-image" INTERFACE deps/stb_image.h)

target_compile_definitions("gl-game" PRIVATE "GLEW_STATIC")
target_compile_options("gl-game" PRIVATE "-Wall")
target_compile_options("gl-game" PRIVATE "-O0")
target_compile_options("gl-game" PRIVATE "-m64")
target_compile_options("gl-game" PRIVATE "-g")
target_compile_options("gl-game" PRIVATE "-finput-charset=UTF-8")

target_link_options("gl-game" PRIVATE "-static" "-m64")
target_link_libraries("gl-game" "glew" "glfw")
target_link_libraries("gl-game" "opengl32" "-lglu32" "-lgdi32")
target_link_libraries("gl-game" "libsrt" "stb-image")
