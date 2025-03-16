#include <chrono>
#include <iomanip>
#include <sstream>

#include "../src/Window.h"
#include "../src/GUI.h"
#include "DebugConsole.h"

int main() {
    if (!Globals::Window) return -1;

    GUI::Initialize();

    // Main loop
    int cycle = 0;
    while (!glfwWindowShouldClose(Globals::Window)) {
        auto before = std::chrono::high_resolution_clock::now();

        // Data dump in console (~60 cycles / second, 3600 cycles = 1 minute)
        if (cycle == 360) {
            auto now = std::chrono::system_clock::now();
            auto now_time = std::chrono::system_clock::to_time_t(now);

            // Use localtime_s for thread-safe and secure local time
            std::tm tm_info{};
            localtime_s(&tm_info, &now_time);

            // Format and print with timestamp
            std::ostringstream oss;
            oss << "[" << std::put_time(&tm_info, "%Y-%m-%d %H:%M:%S") << "] "
                << "Framerate: " << std::fixed << std::setprecision(1) << Globals::Framerate << " ms";

            DebugConsole::AddLog(oss.str().c_str());

            cycle = 0;
        }

        // Clear the framebuffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GUI::Start();
        GUI::Render();

        // Swap buffers and poll events
        glfwSwapBuffers(Globals::Window);

        // Calculate Framerate
        auto after = std::chrono::high_resolution_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count();
        Globals::Framerate = 1000.0f/static_cast<float>(elapsed_ms);

        cycle += 1;
    }

    GUI::Delete();

    glfwDestroyWindow(Globals::Window);
    glfwTerminate();

    return 0;
}