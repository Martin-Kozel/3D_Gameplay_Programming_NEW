# OpenGL VBA Project

> **Note:** This project introduces Vertex Buffer Arrays (VBAs) in OpenGL. It serves as a stepping stone between immediate mode rendering and more advanced concepts like VBOs that will be covered later.

This project demonstrates the use of Vertex Buffer Arrays for efficient vertex data management in OpenGL.

## Project Overview

* Introduction to vertex-based OpenGL graphics
* Demonstrates Vertex Buffer Array usage for basic shapes
* Shows the transition from immediate mode to vertex arrays
* Uses GLFW for window management and OpenGL context creation

## Prerequisites

### Windows (MSYS2)
1. Download and install [MSYS2](https://www.msys2.org/) 
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

## Project Structure
```
.
├── include/             # Header files for declarations
│   └── game.h           # VBA structure and functions
├── src/                 # Source files for implementation
│   ├── main.c           # Entry point of the application
│   └── game.c           # VBA implementation and logic
├── Makefile             # Build configuration
└── README.md            # Project documentation
```

## Technical Details

### Implementation Features
* Basic Vertex Buffer Array setup
* Vertex data organization
* Color per vertex support
* Simple 3D transformations
* Transition from immediate mode to VBAs

### VBA Structure
* Vertex positions (x, y, z)
* Vertex colors (r, g, b)
* Support for multiple primitives:
  - GL_TRIANGLES
  - GL_TRIANGLE_STRIP

### Key OpenGL Functions Used
* `glEnableClientState()`
* `glVertexPointer()`
* `glColorPointer()`
* `glDrawArrays()`

### Controls
* Basic view movement with arrow keys
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

## Known Issues
* Limited to fixed-function pipeline
* Basic vertex attribute support
* No index buffer support (will be covered in VBO topic)
* Fixed vertex format

## Future Improvements
* Add support for texture coordinates
* Implement basic lighting
* Add more primitive types
* Include vertex data manipulation examples
* Prepare for transition to VBOs (next topic)

## Useful Resources
* [OpenGL](https://registry.khronos.org/OpenGL-Refpages/gl4/)
* [GLFW](https://www.glfw.org/)
* [OpenGL Fixed-Function Pipeline](https://www.khronos.org/opengl/wiki/Fixed_Function_Pipeline)
* [Vertex Arrays](https://www.khronos.org/opengl/wiki/Vertex_Specification#Vertex_Arrays)

## Contact
For questions or support, contact:

* muddygames