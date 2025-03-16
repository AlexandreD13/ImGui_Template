#ifndef DEBUG_CONSOLE_H
#define DEBUG_CONSOLE_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdarg>

#include "../src/Globals.h"

class DebugConsole {
public:
    DebugConsole() = default;

    ~DebugConsole() = default;

    static void AddLog(const char* fmt, ...);

    static void Clear();

    static void Render();

private:
    static std::vector<std::string> logs;
    static bool scrollToBottom;
};

#endif