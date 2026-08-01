#pragma once
#include "AppState.hpp"
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/event.hpp>

class UI {
public:
    void run(AppState& state);
private:
    ftxui::Element render_layout(AppState& state);
    ftxui::Element render_file_list(AppState& state);
    ftxui::Element render_preview(AppState& state);
    ftxui::Element render_status_bar(AppState& state);
    bool handle_events(AppState& state, const ftxui::Event& event);
};
