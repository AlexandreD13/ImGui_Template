#ifndef GUI_H
#define GUI_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>

#include "Globals.h"

class GUI {
public:
    static void Initialize();

    static void Start();

    static void Render();

    static void Delete();

    static void ProcessKeyPresses();

    static void SetOverlayStyle();

    static void MenuBar();

    static void TopMenu();

    static void LeftSideMenu();

    static void RightSideMenu();

    static void CreateSliderWithLabel(const char *label, float *value, float min, float max, const char *format) {
        float availableWidth = ImGui::GetContentRegionAvail().x - 5.0f;

        ImGui::Text("%s:", label);
        ImGui::PushItemWidth(availableWidth);
        ImGui::SliderFloat(std::string("##").append(label).c_str(), value, min, max, format);
        ImGui::PopItemWidth();
    }

    static void ShowAboutWindow();
};


#endif
