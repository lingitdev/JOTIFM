#include "UI.hpp"

using namespace ftxui;

Element UI::render_file_list(AppState& state) {
    Elements list_elements;
    for (size_t i = 0; i < state.items.size(); ++i) {
        std::string prefix = state.items[i].is_directory ? "[D] " : "    ";
        std::string text_str = prefix + state.items[i].name;
        
        if (static_cast<int>(i) == state.selected_index) {
            list_elements.push_back(text(text_str) | inverted | bold);
        } else {
            list_elements.push_back(text(text_str));
        }
    }
    if (list_elements.empty()) {
        list_elements.push_back(text("Folder is empty."));
    }
    return window(text(state.current_path), vbox(std::move(list_elements)));
}

Element UI::render_preview(AppState& state) {
    return window(text("Preview"), paragraph(state.preview_content));
}

Element UI::render_status_bar(AppState& state) {
    if (state.current_mode != Mode::NORMAL) {
        std::string title = "Input: ";
        if (state.current_mode == Mode::CREATING_FILE) title = "New File Name: ";
        if (state.current_mode == Mode::CREATING_FOLDER) title = "New Folder Name: ";
        if (state.current_mode == Mode::RENAMING) title = "New Name: ";

        return hbox({
            text(title) | bold | color(Color::Yellow),
            text(state.input_buffer) | inverted,
            filler(),
            text(" [Enter: Confirm | ESC: Cancel] ")
        }) | border;
    }

    return hbox({
        text(" F1: Help | F2: Rename | F3: New File | F4: New Folder | F5: Delete "),
        filler(),
        text(state.status_message)
    }) | border;
}

Element UI::render_layout(AppState& state) {
    return vbox({
        hbox({
            render_file_list(state) | flex,
            render_preview(state) | flex
        }) | flex,
        render_status_bar(state)
    });
}

bool UI::handle_events(AppState& state, const Event& event) {
    if (state.current_mode != Mode::NORMAL) {
        if (event == Event::Escape) {
            state.current_mode = Mode::NORMAL;
            state.input_buffer.clear();
            state.status_message = "Operation cancelled.";
            return true;
        }

        if (event == Event::Return) {
            if (state.current_mode == Mode::CREATING_FILE) state.create_new_file();
            else if (state.current_mode == Mode::CREATING_FOLDER) state.create_new_folder();
            else if (state.current_mode == Mode::RENAMING) state.rename_selected_item();
            return true;
        }

        if (event == Event::Backspace) {
            if (!state.input_buffer.empty()) state.input_buffer.pop_back();
            return true;
        }

        if (event.is_character()) {
            state.input_buffer += event.character();
            return true;
        }

        return false;
    }

    if (event == Event::F1) {
        state.show_help();
        return true;
    }
    if (event == Event::F2) {
        if (!state.items.empty()) {
            state.current_mode = Mode::RENAMING;
            state.input_buffer = state.items[state.selected_index].name;
        }
        return true;
    }
    if (event == Event::F3) {
        state.current_mode = Mode::CREATING_FILE;
        state.input_buffer = "";
        return true;
    }
    if (event == Event::F4) {
        state.current_mode = Mode::CREATING_FOLDER;
        state.input_buffer = "";
        return true;
    }
    if (event == Event::F5) {
        state.delete_selected_item();
        return true;
    }

    // Navigation Keys
    if (event == Event::ArrowDown) { state.select_next(); return true; }
    if (event == Event::ArrowUp) { state.select_previous(); return true; }
    if (event == Event::Return) { state.enter_selected(); return true; }
    if (event == Event::Backspace) { state.go_to_parent(); return true; }

    return false;
}

void UI::run(AppState& state) {
    auto screen = ScreenInteractive::TerminalOutput();
    state.refresh();

    auto component = Renderer([&] {
        return render_layout(state);
    });

    component = CatchEvent(component, [&](Event event) {
        if (event == Event::Character('q') || event == Event::Character('Q')) {
            // Allow typing 'q' in input mode without quitting the application
            if (state.current_mode != Mode::NORMAL) {
                return handle_events(state, event);
            }
            screen.ExitLoopClosure()();
            return true;
        }
        return handle_events(state, event);
    });

    screen.Loop(component);
}