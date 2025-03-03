# OpenGL Cube Project

> **Note:** This project is a port of a previous SFML Starter Kit. This StarterKit uses GLFW as opposed to SFML, providing a lightweight alternative for OpenGL context creation and window management.

This project demonstrates basic OpenGL functionality by rendering and animating a rotating 3D cube. It serves as an introduction to OpenGL programming concepts including display lists, perspective projection, and basic animation.

## Project Overview

* Simple OpenGL application demonstrating 3D graphics
* Features a rotating cube with colored faces
* Implements basic game loop architecture
* Uses GLFW for window management and OpenGL context creation

## Prerequisites

### Windows (MSYS2)
1. Download and install MSYS2 from https://www.msys2.org/
2. Launch MSYS2 UCRT64 terminal: `C:\msys64\ucrt64.exe`
3. Update package database:
   ```bash
   pacman -Syu
   ```
4. Install required packages:
   ```bash
   pacman -S make
   pacman -S git
   pacman -S mingw-w64-ucrt-x86_64-gcc
   pacman -S mingw-w64-ucrt-x86_64-glfw
   pacman -S mingw-w64-ucrt-x86_64-mesa
   ```

### Linux (Ubuntu/Debian)
1. Update package database:
   ```bash
   sudo apt update
   ```
2. Install required packages:
   ```bash
   sudo apt install build-essential
   sudo apt install git
   sudo apt install libglfw3-dev
   sudo apt install libglu1-mesa-dev
   sudo apt install mesa-common-dev
   ```

### Linux (Fedora)
```bash
sudo dnf install make
sudo dnf install gcc
sudo dnf install glfw-devel
sudo dnf install mesa-libGL-devel
sudo dnf install mesa-libGLU-devel
```

## Building the Project

### Windows (MSYS2)
1. Launch MSYS2 UCRT64 terminal
2. Clone the repository:
   ```bash
   cd /c/projects
   git clone <repository-url>
   cd <project-directory>
   ```
3. Build the project:
   ```bash
   make
   ```

### Linux
1. Open terminal
2. Clone the repository:
   ```bash
   mkdir -p ~/projects
   cd ~/projects
   git clone <repository-url>
   cd <project-directory>
   ```
3. Build the project:
   ```bash
   make
   ```

## Project Structure
```
.
├── include/
│   └── game.h           # Game structure and function declarations
├── src/
│   ├── main.c          # Entry point
│   └── game.c          # Game implementation
├── Makefile            # Build configuration
└── README.md           # This file
```

## Technical Details

### Implementation Features
* 3D perspective projection
* Display list usage for efficient rendering
* Double buffering for smooth animation
* Basic game structure with initialize/update/draw loop
* Color-per-face rendering

### Controls
* The cube automatically rotates around the Z-axis
* Close window to exit the application

## Troubleshooting

### Windows
1. If MSYS2 packages fail to install:
   ```bash
   pacman -Syu --needed
   ```
2. If compiler is not found:
   * Verify PATH includes: `C:\msys64\ucrt64\bin`
   * Restart MSYS2 terminal

### Linux
1. If OpenGL headers are not found:
   ```bash
   # Ubuntu/Debian
   sudo apt install mesa-common-dev

   # Fedora
   sudo dnf install mesa-libGL-devel
   ```
2. If GLFW is not found:
   ```bash
   # Ubuntu/Debian
   sudo apt install libglfw3-dev

   # Fedora
   sudo dnf install glfw-devel
   ```

## Known Issues
* Immediate mode rendering is deprecated in modern OpenGL
* No error handling for OpenGL functions
* Fixed window size (800x600)

## Future Improvements
* Implement modern OpenGL practices (VBOs, VAOs, shaders)
* Add texture support
* Implement camera controls
* Add more complex animations
* Include error handling

## Contact
For questions or support, contact:
* muddygames