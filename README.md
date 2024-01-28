# To clean buildsystem & artefacts

Run `rmdir /s /q build && del compile_commands.json`

# Make a fresh build (generate MSYS makefiles) - Mingw should be installed (if using Windows):

Run `cmake -B ./build -G "MSYS Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1
&&cmake --build build&&copy .\build\compile_commands.json .\compile_commands.json`

(compile_commands.json is used by clangd to understand what compiler commands and source/header files are included in the build, meaning the build configuration does not have to be re-iterated outside CMake files)
