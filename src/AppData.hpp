#pragma once
#include "FileEngine.hpp"
#include <string>
#include <vector>
#include <filesystem>

enum class Mode {
    NORMAL,
    CREATING_FILE,
    CREATING_FOLDER,
    RENAMING
};

class AppState {
public:
    Engine engine;
    std::string root_path;
    std::string current_path;
    std::vector<FileItem> items;
    int selected_index = 0;
    std::string preview_content;
    std::string status_message = "Ready";

    Mode current_mode = Mode::NORMAL;
    std::string input_buffer = "";

    AppState(const std::string& start_dir = ".") {
        try {
            root_path = fs::canonical(start_dir).string();
        } catch (...) {
            root_path = fs::current_path().string();
        }
        current_path = root_path;
    }

    void refresh();
    void select_next();
    void select_previous();
    void enter_selected();
    void go_to_parent();
    void update_preview();

    void show_help();
    void create_new_file();
    void create_new_folder();
    void delete_selected_item();
    void rename_selected_item();
};
