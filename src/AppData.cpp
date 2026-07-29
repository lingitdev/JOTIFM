#include "AppState.hpp"
#include <fstream>

void AppState::refresh() {
    items = engine.list_directory(current_path);
    if (items.empty()) {
        selected_index = 0;
    } else if (selected_index >= static_cast<int>(items.size())) {
        selected_index = items.size() - 1;
    }
    update_preview();
}

void AppState::select_next() {
    if (!items.empty() && selected_index < static_cast<int>(items.size()) - 1) {
        selected_index++;
        update_preview();
    }
}

void AppState::select_previous() {
    if (selected_index > 0) {
        selected_index--;
        update_preview();
    }
}

void AppState::enter_selected() {
    if (items.empty() || selected_index < 0 || selected_index >= static_cast<int>(items.size()))
        return;
    const auto& selected = items[selected_index];
    if (selected.is_directory) {
        current_path = selected.full_path;
        selected_index = 0;
        status_message = "Ready";
        refresh();
    }
}

void AppState::go_to_parent() {
    if (fs::equivalent(current_path, root_path)) {
        status_message = "Cannot go above root directory!";
        return;
    }

    fs::path p(current_path);
    if (p.has_parent_path()) {
        current_path = p.parent_path().string();
        selected_index = 0;
        status_message = "Ready";
        refresh();
    }
}

void AppState::update_preview() {
    if (items.empty() || selected_index < 0 || selected_index >= static_cast<int>(items.size())) {
        preview_content = "No item selected.";
        return;
    }
    const auto& selected = items[selected_index];
    if (selected.is_directory) {
        preview_content = "[ Directory ]\nPress Enter to open.";
    } else {
        std::ifstream file(selected.full_path);
        if (file.is_open()) {
            std::string line;
            preview_content = "";
            int line_count = 0;
            while (std::getline(file, line) && line_count < 20) {
                preview_content += line + "\n";
                line_count++;
            }
        } else {
            preview_content = "Could not read file content.";
        }
    }
}

void AppState::show_help() {
    status_message = "F1: Help | F2: Rename | F3: File | F4: Folder | F5: Delete";
}

void AppState::create_new_file() {
    if (input_buffer.empty()) {
        status_message = "Error: File name cannot be empty!";
        current_mode = Mode::NORMAL;
        return;
    }
    bool success = engine.create_file(current_path, input_buffer);
    if (success) {
        status_message = "File created: " + input_buffer;
        refresh();
    } else {
        status_message = "Error: Could not create file!";
    }
    input_buffer.clear();
    current_mode = Mode::NORMAL;
}

void AppState::create_new_folder() {
    if (input_buffer.empty()) {
        status_message = "Error: Folder name cannot be empty!";
        current_mode = Mode::NORMAL;
        return;
    }
    bool success = engine.create_folder(current_path, input_buffer);
    if (success) {
        status_message = "Folder created: " + input_buffer;
        refresh();
    } else {
        status_message = "Error: Could not create folder!";
    }
    input_buffer.clear();
    current_mode = Mode::NORMAL;
}

void AppState::delete_selected_item() {
    if (items.empty() || selected_index < 0 || selected_index >= static_cast<int>(items.size())) {
        status_message = "No item selected to delete!";
        return;
    }

    std::string path_to_delete = items[selected_index].full_path;
    bool success = engine.delete_item(path_to_delete);

    if (success) {
        status_message = "Successfully deleted: " + items[selected_index].name;
        refresh();
    } else {
        status_message = "Error: Could not delete item!";
    }
}

void AppState::rename_selected_item() {
    if (items.empty() || selected_index < 0 || selected_index >= static_cast<int>(items.size())) {
        status_message = "No item selected to rename!";
        current_mode = Mode::NORMAL;
        return;
    }

    if (input_buffer.empty()) {
        status_message = "Error: New name cannot be empty!";
        current_mode = Mode::NORMAL;
        return;
    }

    std::string old_path = items[selected_index].full_path;
    std::string new_path = (fs::path(current_path) / input_buffer).string();

    bool success = engine.rename_item(old_path, new_path);
    if (success) {
        status_message = "Renamed to: " + input_buffer;
        refresh();
    } else {
        status_message = "Error: Could not rename item!";
    }
    input_buffer.clear();
    current_mode = Mode::NORMAL;
}
