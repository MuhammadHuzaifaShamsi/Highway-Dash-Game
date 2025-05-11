
# 🚗 OOP Car Game Project

## 📜 Project Description

This is a fun and interactive 2D car game developed in **C++** using **Object-Oriented Programming** principles. It leverages the **SFML (Simple and Fast Multimedia Library)** for graphics rendering, audio playback, and handling user input.

## 🎮 How It Works

- Game loop is handled in `main.cpp`, which repeatedly initializes and runs a new `Game` session.
- `Game.h` and `Game.cpp` contain the main gameplay logic.
- Assets (images, sounds, fonts) are loaded and rendered in real-time.
- Players control a car, avoid obstacles, and enjoy sound effects and visuals.

## ✨ Features

- 🚗 Smooth car movement
- ⛔ Obstacle spawning and collision detection
- 🔊 Background music and crash sounds
- 🖼️ Custom UI with fonts and graphics
- 🔁 Auto-restart after game over

## 🗂️ Folder Structure

```
├── main.cpp              # Entry point
├── Game.cpp / Game.h     # Game logic
├── cars/                 # Car and UI images
├── sound/                # Sound effects and music
├── font/                 # Custom fonts
├── src/include/          # SFML headers
├── src/lib/              # SFML libraries
├── .vscode/              # VSCode configurations
├── MakeFile              # Optional build file
└── game.exe              # Windows executable
```

## 🛠️ Requirements

- C++17 or newer
- SFML 2.x
- Windows OS (for executable)
- VSCode or any C++ IDE (optional)

## ▶️ Running the Game

### Option 1: Run Executable
Just double-click `game.exe` on a Windows machine.

### Option 2: Build from Source
1. Install SFML and a C++ compiler (e.g., g++, MSVC).
2. Use provided `MakeFile` or configure your IDE.
3. Compile and run.

## 👨‍💻 Author
**Enjoy playing the game!**
