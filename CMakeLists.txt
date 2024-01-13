cmake_minimum_required(VERSION 3.21)

project(gl-game)

set(CMAKE_CXX_STANDARD C++17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable("gl-game")

file(GLOB_RECURSE sources RELATIVE impl/**/*.cpp)
file(GLOB_RECURSE headers RELATIVE impl/**/*.h)

target_sources("gl-game" PRIVATE FILE_SET source BASE_DIRS impl FILES source-files)
target_sources("gl-game" PRIVATE FILE_SET headers BASE_DIRS impl FILES header-files)

add_library()

target_include_directories()

target_compile_definitions()
target_compile_features()
target_compile_options()

target_link_directories()
target_link_libraries()
target_link_options()
