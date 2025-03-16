#ifndef GLOBALS_H
#define GLOBALS_H

#include "../src/Window.h"
#include "imgui.h"

class Globals {
public:
    Globals(const Globals&) = delete;
    Globals& operator=(const Globals&) = delete;

    static Globals& getInstance() {
        static Globals instance;
        return instance;
    }

    // App settings
    static const char *AppName;
    static int WindowWidth;
    static int WindowHeight;
    static GLFWwindow *Window;

    // UI States
    static bool IsOverlayVisible;
    static bool ShowAboutWindow;
    static bool IsDebugConsoleVisible;

    // UI Style
    static float OverlayWidth;
    static float TopMenuHeight;

    static float FontScale;

    static float FontSize;
    static float MenuBarFontSize;

    static ImFont* DefaultFont;
    static ImFont* DefaultFontItalic;

    static ImFont* MenuBarFont;
    static ImFont* MenuBarFontItalic;

    static const char *FontPath;
    static const char *FontPathItalic;

    // Performance monitoring
    static float Framerate;
private:
    Globals() {}
};

#endif //_GLOBALS_H