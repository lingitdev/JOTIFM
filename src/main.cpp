#include "AppState.hpp"
#include "UI.hpp"

int main(int argc, char* argv[]) {
    std::string start_dir = ".";
    if (argc > 1) {
        start_dir = argv[1];
    }

    AppState state(start_dir);
    UI ui;
    ui.run(state);
    return 0;
}
