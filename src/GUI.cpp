#include "../src/GUI.h"
#include "DebugConsole.h"

void GUI::Initialize() {
    DebugConsole::AddLog("\nOpening application ImGui Template...\n\n");

    glfwGetWindowSize(Globals::Window, &Globals::WindowWidth, &Globals::WindowHeight);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    io.FontGlobalScale = Globals::FontScale;

    ImGui_ImplGlfw_InitForOpenGL(Globals::Window, true);
    ImGui_ImplOpenGL3_Init();

    SetOverlayStyle();
}

void GUI::Start() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUI::Render() {
    glfwPollEvents();
    ProcessKeyPresses();

    if (!Globals::IsOverlayVisible) {
        ImGui::Render();
        return;
    }

    if (!Globals::IsDebugConsoleVisible) {
        DebugConsole::Render();
    }

    if (Globals::ShowAboutWindow) {
        ShowAboutWindow();
    }

    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2((float) Globals::WindowWidth, (float) Globals::WindowHeight), ImGuiCond_Always);

    ImGui::Begin(
            "Menu",
            nullptr,
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_MenuBar |
            ImGuiWindowFlags_NoBringToFrontOnFocus
    );

    MenuBar();
    TopMenu();
    LeftSideMenu();
    RightSideMenu();

    // ImGui::ShowDemoWindow();

    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::Delete() {
    DebugConsole::AddLog("\nClosing application ImGui Template...\n");

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GUI::ProcessKeyPresses() {
    //static bool wasKeyPressed = false;
    static bool wasKeyPressedForDebugConsole = false;

    static int closeApp = GLFW_KEY_ESCAPE;
    //static int hideMenu = GLFW_KEY_M;
    static int debugConsole = GLFW_KEY_C;

    // Close application
    if (glfwGetKey(Globals::Window, closeApp) == GLFW_PRESS) {
        glfwSetWindowShouldClose(Globals::Window, GL_TRUE);
    }

    // Debug Console
    if (glfwGetKey(Globals::Window, debugConsole) == GLFW_PRESS) {
        if (!wasKeyPressedForDebugConsole) {
            Globals::IsDebugConsoleVisible = !Globals::IsDebugConsoleVisible;
            wasKeyPressedForDebugConsole = true;
        }
    } else {
        wasKeyPressedForDebugConsole = false;
    }

//    // Show / Hide menu
//    if (glfwGetKey(Globals::Window, hideMenu) == GLFW_PRESS) {
//        if (!wasKeyPressed) {
//            Globals::IsOverlayVisible = !Globals::IsOverlayVisible;
//            wasKeyPressed = true;
//        }
//    } else {
//        wasKeyPressed = false;
//        if (wasKeyPressed && glfwGetKey(Globals::Window, hideMenu) == GLFW_RELEASE) {
//            wasKeyPressed = false;
//        }
//    }
}

void GUI::SetOverlayStyle() {
    // ImGui::StyleColorsDark();     // Dark Theme
    // ImGui::StyleColorsClassic();  // Classic theme
    ImGui::StyleColorsLight();    // Light Theme

    ImGuiIO &io = ImGui::GetIO();

    io.Fonts->Clear();

    ImFont* defaultFont = io.Fonts->AddFontFromFileTTF(Globals::FontPath, Globals::FontSize);
    ImFont* defaultFontItalic = io.Fonts->AddFontFromFileTTF(Globals::FontPathItalic, Globals::FontSize);

    ImFont* menuBarFont = io.Fonts->AddFontFromFileTTF(Globals::FontPath, Globals::MenuBarFontSize);
    ImFont* menuBarFontItalic = io.Fonts->AddFontFromFileTTF(Globals::FontPathItalic, Globals::MenuBarFontSize);

    // Build font atlas
    io.Fonts->Build();

    // Store fonts in global/static variables
    Globals::DefaultFont = defaultFont;
    Globals::DefaultFontItalic = defaultFontItalic;

    Globals::MenuBarFont = menuBarFont;
    Globals::MenuBarFontItalic = menuBarFontItalic;
}

void GUI::MenuBar() {
    ImGui::PushFont(Globals::MenuBarFont);

    ImGuiStyle &style = ImGui::GetStyle();

    style.WindowBorderSize = 0.5f;
    style.Alpha = 1.0f;

    style.FrameRounding = 0.0f;
    style.GrabRounding = 0.0f;
    style.WindowRounding = 0.0f;
    style.PopupRounding = 0.0f;

    style.ItemSpacing = ImVec2(5.0f, 5.0f);
    style.ItemInnerSpacing = ImVec2(0.0f, 5.0f);

    style.FramePadding = ImVec2(0.0f, 3.0f);
    style.WindowPadding = ImVec2(0.0f, 0.0f);

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 3.0f);
            if (ImGui::MenuItem("New")) {}

            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 3.0f);
            if (ImGui::MenuItem("Open", "Ctrl+O")) {}

            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 3.0f);
            if (ImGui::MenuItem("Save", "Ctrl+S")) {}

            // Full-width separator
            float separatorStartX = ImGui::GetWindowPos().x;
            float separatorWidth = 40.0f;
            ImGui::SetCursorPosX(0);
            ImGui::Separator();
            ImGui::SetCursorPosX(separatorStartX + separatorWidth);
            ImGui::SetCursorPosX(0);

            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 3.0f);
            if (ImGui::MenuItem("Exit")) {
                glfwSetWindowShouldClose(Globals::Window, GL_TRUE);
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit")) {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 3.0f);
            if (ImGui::MenuItem("Undo", "Ctrl+Z")) {}

            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 3.0f);
            if (ImGui::MenuItem("Redo", "Ctrl+Y", false, false)) {}

            ImGui::Separator();

            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 3.0f);
            if (ImGui::MenuItem("Cut", "Ctrl+X")) {}

            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 3.0f);
            if (ImGui::MenuItem("Copy", "Ctrl+C")) {}

            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 3.0f);
            if (ImGui::MenuItem("Paste", "Ctrl+V")) {}

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Image")) {
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Layer")) {
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Type")) {
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Select")) {
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Filter")) {
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("3D")) {
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View")) {
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Window")) {
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help")) {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 3.0f);
            if (ImGui::MenuItem("About")) {
                Globals::ShowAboutWindow = true;
            }

            ImGui::EndMenu();
        }

        ImGui::PopFont();
        ImGui::PushFont(Globals::MenuBarFontItalic);

        char framerateText[32];
        snprintf(framerateText, sizeof(framerateText), "Framerate: %.1f ms", Globals::Framerate);

        float textWidth = ImGui::CalcTextSize(framerateText).x + 10.0f;
        float windowWidth = ImGui::GetWindowWidth();
        float padding = style.ItemSpacing.x;

        ImGui::SameLine(windowWidth - textWidth - padding);
        ImGui::Text("%s", framerateText);

        ImGui::EndMainMenuBar();
    }

    ImGui::PopFont();
}

void GUI::TopMenu() {
    ImGui::PushFont(Globals::DefaultFont);

    ImGuiStyle &style = ImGui::GetStyle();

    style.WindowPadding = ImVec2(0, 0);
    style.WindowBorderSize = 0.5f;
    style.Alpha = 1.0f;

    style.FrameRounding = 0.0f;
    style.GrabRounding = 0.0f;
    style.WindowRounding = 0.0f;
    style.PopupRounding = 0.0f;

    style.ItemSpacing = ImVec2(0.0f, 5.0f);
    style.FramePadding = ImVec2(10.0f, 5.0f);

    ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetFrameHeight() - 8.0f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2((float) Globals::WindowWidth, Globals::TopMenuHeight), ImGuiCond_Always);

    if (ImGui::Begin(
            "Top Menu",
            nullptr,
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoScrollbar
    )) {
        if (ImGui::Button("Button 1")) {}

        ImGui::SameLine();

        if (ImGui::Button("Button 2")) {}

        ImGui::SameLine();

        if (ImGui::Button("Button 3")) {}

        ImGui::End();
    }

    ImGui::PopFont();
}

void GUI::LeftSideMenu() {
    ImGui::PushFont(Globals::DefaultFont);

    ImGuiStyle &style = ImGui::GetStyle();

    style.WindowPadding = ImVec2(10, 10);
    style.WindowBorderSize = 0.5f;
    style.Alpha = 1.0f;

    style.FrameRounding = 0.0f;
    style.GrabRounding = 0.0f;
    style.WindowRounding = 0.0f;
    style.PopupRounding = 0.0f;

    style.ItemSpacing = ImVec2(10.0f, 5.0f);
    style.FramePadding = ImVec2(10.0f, 5.0f);

    float menuBarHeight = ImGui::GetFrameHeight() + 1;

    ImGui::SetNextWindowPos(ImVec2(0.0f, menuBarHeight + Globals::TopMenuHeight - 8.0f), ImGuiCond_Always, ImVec2(0.0f, 0.0f));

    ImGui::SetNextWindowSize(ImVec2(Globals::OverlayWidth, ((float) Globals::WindowHeight - ImGui::GetFrameHeight() - Globals::TopMenuHeight + 1)),
                             ImGuiCond_Once);

    ImGui::SetNextWindowSizeConstraints(ImVec2(Globals::OverlayWidth, (float) Globals::WindowHeight),
                                        ImVec2((float) Globals::WindowWidth / 3.0f, (float) Globals::WindowHeight));

    if (ImGui::Begin("Left Menu", nullptr,
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar)) {
        static float saturation = 1.0f;
        CreateSliderWithLabel("Saturation", &saturation, 0.0f, 2.0f, "%.2f");

        static float hue = 0.0f;
        CreateSliderWithLabel("Hue", &hue, -180.0f, 180.0f, "%.2f");

        static float contrast = 1.0f;
        CreateSliderWithLabel("Contrast", &contrast, 0.0f, 2.0f, "%.2f");

        static float brightness = 1.0f;
        CreateSliderWithLabel("Brightness", &brightness, 0.0f, 2.0f, "%.2f");

        static float details = 1.0f;
        CreateSliderWithLabel("Details", &details, 0.0f, 2.0f, "%.2f");

        if (ImGui::Button("Reset")) {
            saturation = 1.0f;
            hue = 0.0f;
            contrast = 1.0f;
            brightness = 1.0f;
            details = 1.0f;
        }

        ImGui::End();
    }

    ImGui::PopFont();
}

void GUI::RightSideMenu() {
    ImGui::PushFont(Globals::DefaultFont);

    ImGuiStyle &style = ImGui::GetStyle();

    style.WindowPadding = ImVec2(10, 10);
    style.WindowBorderSize = 0.5f;
    style.Alpha = 1.0f;

    style.FrameRounding = 0.0f;
    style.GrabRounding = 0.0f;
    style.WindowRounding = 0.0f;
    style.PopupRounding = 0.0f;

    style.ItemSpacing = ImVec2(10.0f, 5.0f);
    style.FramePadding = ImVec2(10.0f, 5.0f);

    float menuBarHeight = ImGui::GetFrameHeight() + 1;

    ImGui::SetNextWindowPos(ImVec2((float) (Globals::WindowWidth), menuBarHeight + Globals::TopMenuHeight - 8.0f), ImGuiCond_Always,
                            ImVec2(1.0f, 0.0f));

    ImGui::SetNextWindowSize(ImVec2(Globals::OverlayWidth, ((float) Globals::WindowHeight - menuBarHeight - Globals::TopMenuHeight + 1)),
                             ImGuiCond_Once);

    ImGui::SetNextWindowSizeConstraints(ImVec2(Globals::OverlayWidth, (float) Globals::WindowHeight),
                                        ImVec2((float) Globals::WindowWidth / 3.0f, (float) Globals::WindowHeight));

    if (ImGui::Begin("Right Menu", nullptr,
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar)) {
        static float saturation = 1.0f;
        CreateSliderWithLabel("Saturation", &saturation, 0.0f, 2.0f, "%.2f");

        static float hue = 0.0f;
        CreateSliderWithLabel("Hue", &hue, -180.0f, 180.0f, "%.2f");

        static float contrast = 1.0f;
        CreateSliderWithLabel("Contrast", &contrast, 0.0f, 2.0f, "%.2f");

        static float brightness = 1.0f;
        CreateSliderWithLabel("Brightness", &brightness, 0.0f, 2.0f, "%.2f");

        static float details = 1.0f;
        CreateSliderWithLabel("Details", &details, 0.0f, 2.0f, "%.2f");

        if (ImGui::Button("Reset")) {
            saturation = 1.0f;
            hue = 0.0f;
            contrast = 1.0f;
            brightness = 1.0f;
            details = 1.0f;
        }

        ImGui::End();
    }

    ImGui::PopFont();
}

void GUI::ShowAboutWindow() {
    ImGuiIO &io = ImGui::GetIO();
    ImVec2 center = ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);

    ImGui::SetNextWindowPos(center, ImGuiCond_Once, ImVec2(0.5f, 0.5f));

    ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.26f, 0.59f, 0.98f, 0.4f));
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.26f, 0.59f, 0.98f, 1.0f));

    ImGui::Begin("About", &Globals::ShowAboutWindow, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);

    ImGui::PopStyleColor(2);

    ImGui::Text("LightFX");
    float rightAlign = ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("v0.1").x;
    ImGui::SameLine(rightAlign);
    ImGui::PushFont(Globals::DefaultFontItalic);
    ImGui::Text("v0.1");
    ImGui::PopFont();

    ImGui::Text("Developed by");
    ImGui::SameLine();
    ImGui::PushFont(Globals::DefaultFontItalic);
    ImGui::Text("Alexandre Desfossés");
    ImGui::PopFont();

    ImGui::Text("Year");
    rightAlign = ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("2025").x;
    ImGui::SameLine(rightAlign);
    ImGui::PushFont(Globals::DefaultFontItalic);
    ImGui::Text("2025");
    ImGui::PopFont();

    ImGui::End();
}

