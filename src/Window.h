#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


class Window {
public:
    static Window& getInstance() {
        static Window instance;
        return instance;
    }

    static GLFWwindow *initializeWindow(int width, int height, const char *title);
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
};

#endif // WINDOW_H