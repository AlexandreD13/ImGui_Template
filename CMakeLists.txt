cmake_minimum_required(VERSION 3.27)
project(ImGui_Template)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        "src/*.cpp"
        "src/**/*.h"
        "dependencies/**/*.cpp"
        "dependencies/**/*.h"
        "dependencies/**/*.c"
)

add_executable(ImGui_Template ${SOURCES}
        src/GUI.cpp
        src/GUI.h
        src/Globals.cpp
        src/DebugConsole.cpp)

target_include_directories(ImGui_Template PRIVATE
        dependencies
        dependencies/glad/include
        dependencies/glad/include/glad
        dependencies/glad/include/KHR
        dependencies/GLFW
        dependencies/glm
        dependencies/glm/detail
        dependencies/glm/ext
        dependencies/glm/gtc
        dependencies/glm/gtx
        dependencies/glm/simd
        dependencies/imgui
        dependencies/stb
)

target_link_directories(ImGui_Template PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/GLFW/lib/)
target_link_libraries(ImGui_Template glfw3 opengl32)