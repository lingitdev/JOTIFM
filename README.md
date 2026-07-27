JOTIFM - JOTIFM IS not a File Manager

    JOTIFM (JOTIFM IS not a File Manager) is a lightweight, terminal-based note-taking application written in C++17 using the FTXUI library.

While it currently utilizes directory-navigation features to organize and browse text notes, JOTIFM is fundamentally designed as a distraction-free keyboard-driven workspace for your notes.
🚀 Features

    Dual-Pane Note Browser: Browse note directories on the left and immediately preview note contents on the right.

    Live Content Preview: Renders text note contents up to 20 lines without opening the file.

    Note & Directory Management:
        New Note (F3): Instantly drop a new note file.
        New Category/Folder (F4): Organize notes into subfolders.
        Rename (F2): Quickly rename notes or categories inline.
        Delete (F5): Remove unwanted notes/folders.
    Contextual Input Bar: Smooth note creation and renaming flows with Enter (confirm) and ESC (cancel).

⌨️ Keyboard Shortcuts
Navigation & Viewing
Key	Action
Arrow Up / Arrow Down	Navigate through notes & categories
Enter	Open category / folder
Backspace	Go up to parent category
q / Q	Exit application (when not typing)
Note Operations
Key	Action
F1	Show help / status info
F2	Rename active note or category
F3	Create new note file
F4	Create new category (folder)
F5	Delete selected note/folder
🚧 Roadmap / Planned Features

    [ ] Custom note editor integration
    [ ] Customizable keybindings
    [ ] Markdown preview & syntax highlighting
    [ ] Fast search / tag filtering across all notes

🛠️ Building & Running
Prerequisites

    C++ Compiler: C++17 support (GCC 8+, Clang 7+, MSVC 2019+)
    CMake: v3.15+

Build Steps
Bash

# Clone the repository
git clone https://github.com/your-username/JOTIFM.git
cd JOTIFM

# Build with CMake
cmake -B build
cmake --build build -j4

# Run JOTIFM
./build/JOTIFM

📄 License

Distributed under the GNU GPLv3.0.
