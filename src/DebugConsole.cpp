#include "../src/DebugConsole.h"

bool DebugConsole::scrollToBottom = true;
std::vector<std::string> DebugConsole::logs;

void DebugConsole::AddLog(const char *fmt, ...) {
    char buffer[1024];

    va_list args;
            va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
            va_end(args);

    logs.emplace_back(buffer);

    if (logs.size() > 10000) {
        logs.erase(logs.begin());
    }

    scrollToBottom = true;
}

void DebugConsole::Clear() {
    logs.clear();
}

void DebugConsole::Render() {
    ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.26f, 0.59f, 0.98f, 0.4f));
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.26f, 0.59f, 0.98f, 1.0f));

    ImGui::Begin("Debug Console", nullptr);
    ImGui::SetWindowSize(ImVec2(0, 0), ImGuiCond_FirstUseEver);

    ImGui::PopStyleColor(2);

    if (ImGui::Button("Clear")) {
        Clear();
    }

    ImGui::Separator();

    ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

    for (const auto& log : logs) {
        ImGui::TextUnformatted(log.c_str());
    }

    if (scrollToBottom) {
        ImGui::SetScrollHereY(1.0f);
    }
    scrollToBottom = false;

    ImGui::EndChild();

    ImGui::End();
}
