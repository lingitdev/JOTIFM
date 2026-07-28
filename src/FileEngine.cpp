#include "FileEngine.hpp"
#include <algorithm>

bool Engine::create_folder(const std::string& path, const std::string& name) {
    try {
        fs::path full_path = fs::path(path) / name;
        return fs::create_directory(full_path);
    } catch (const fs::filesystem_error& e) {
        return false;
    }
}

bool Engine::create_file(const std::string& path, const std::string& name) {
    try {
        fs::path full_path = fs::path(path) / name;
        std::ofstream file(full_path);
        return file.good();
    } catch (const std::exception& e) {
        return false;
    }
}

bool Engine::delete_item(const std::string& path) {
    try {
        fs::path full_path = fs::path(path);
        fs::remove_all(full_path);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

bool Engine::rename_item(const std::string& old_name, const std::string& new_name) {
    try {
        fs::rename(old_name, new_name);
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

std::vector<FileItem> Engine::list_directory(const std::string& path) {
    std::vector<FileItem> items;
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            FileItem item;
            item.name = entry.path().filename().string();
            item.full_path = entry.path().string();
            item.is_directory = entry.is_directory();
            items.push_back(item);
            
        }
    } catch (const std::exception& e) {
        return {};
    }
    return items;
}
