#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

struct FileItem {
    std::string name;
    std::string full_path;
    bool is_directory;
};

class Engine {
public:
    bool create_folder(const std::string& path, const std::string& name);
    bool create_file(const std::string& path, const std::string& name);
    bool delete_item(const std::string& path);
    bool rename_item(const std::string& old_name, const std::string& new_name);
    std::vector<FileItem> list_directory(const std::string& path);
};
