#include "../src/Globals.h"

// App settings
const char *Globals::AppName = "ImGui Template";
int Globals::WindowWidth = 1920;
int Globals::WindowHeight = 1080;
GLFWwindow *Globals::Window = Window::initializeWindow(WindowWidth, WindowHeight, AppName);

// UI States
bool Globals::IsOverlayVisible = true;
bool Globals::ShowAboutWindow = false;
bool Globals::IsDebugConsoleVisible = true;

float Globals::OverlayWidth = 300.0f;
float Globals::TopMenuHeight = 30.0f;

float Globals::FontScale = 1.5f;

float Globals::FontSize = 14.0f;
float Globals::MenuBarFontSize = 12.0f;

ImFont* Globals::DefaultFont;
ImFont* Globals::DefaultFontItalic;

ImFont* Globals::MenuBarFont;
ImFont* Globals::MenuBarFontItalic;

const char *Globals::FontPath = "../Assets/fonts/OpenSans-Regular.ttf";
const char *Globals::FontPathItalic = "../Assets/fonts/OpenSans-BoldItalic.ttf";

// Performance monitoring
float Globals::Framerate = 0.0f;
