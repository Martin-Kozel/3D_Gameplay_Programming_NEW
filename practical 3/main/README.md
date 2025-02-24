# OpenGL Triangle StarterKit with 3D Math Library

> **Note:** This project is a port of a previous SFML Starter Kit. This StarterKit uses GLFW as opposed to SFML, providing a lightweight alternative for OpenGL context creation and window management.

A C-based starter kit demonstrating basic 3D mathematics (Vector3f, Matrix3f) with GLFW and OpenGL. Features an interactive triangle that can be rotated using keyboard controls.

## Features

### Math Components
- **Vector3f**: 3D vector operations with length, normalization, and utility functions
- **Matrix3f**: 3x3 matrix operations supporting rotations around X, Y, and Z axes

### Demo Application
- Renders a blue triangle in 3D space
- Interactive rotation using left/right arrow keys
- Perspective projection setup
- Display list usage for efficient rendering
- Debug output showing vector positions

## Project Structure
```
.
├── include/
│   ├── debug.h       # debug header utility
│   ├── matrix3f.h    # Matrix3f structure and operations
│   ├── quaternion.h  # Quaternion structure and operations
│   ├── vector3f.h    # Vector3f structure and operations
│   └── game.h        # Game structure and function declarations
├── port/
│   ├── Matrix3.cs    # C# Matrix3 to be ported to C/C++
│   ├── Quaternion.cs # C# Quaternion to be ported to C/C++
│   └── Vector3.cs    # C# Vector3 to be ported to C/C++
├── src/
│   ├── matrix3f.c    # Matrix implementation
│   ├── quaternion.c  # Quaternion implementation
│   ├── vector3f.c    # Vector implementation
│   ├── main.c        # mainline
│   └── game.c        # Main game
├── Makefile
└── README.md
```

## Technical Specifications

### Window Settings
- Screen Width: 800 pixels
- Screen Height: 600 pixels
- Field of View: 45 degrees
- Near Plane: 1.0
- Far Plane: 500.0

### Controls
- Left Arrow: Rotate triangle counter-clockwise
- Right Arrow: Rotate triangle clockwise
- Close window to exit

## Prerequisites

### Windows (MSYS2)
1. Install [MSYS2](https://www.msys2.org/)
2. Open MSYS2 UCRT64 terminal
3. Install required packages:
```bash
pacman -Syu
pacman -S mingw-w64-ucrt-x86_64-gcc
pacman -S mingw-w64-ucrt-x86_64-glfw
pacman -S mingw-w64-ucrt-x86_64-mesa
pacman -S make
```

### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install build-essential
sudo apt install libglfw3-dev
sudo apt install libglu1-mesa-dev
sudo apt install mesa-common-dev
```

### Linux (Fedora)
```bash
sudo dnf install gcc
sudo dnf install glfw-devel
sudo dnf install mesa-libGL-devel
```

## Building and Running

### Windows (MSYS2)
```bash
cd /c/projects/opengl-triangle
make
```

### Linux
```bash
cd ~/projects/opengl-triangle
make
```

## Math Library Usage

### Vector Operations
```c
Vector3f v;
init(&v, 0.0f, 2.0f, -5.0f);
float len = length(&v);
normalize(&v);
```

### Matrix Operations
```c
Matrix3f rotationMatrix = rotateZ(45.0f);  // 45-degree rotation around Z-axis
Vector3f rotated = multiplyMatrixByVector(&rotationMatrix, &v);
```

## Implementation Details

### Vector3f Functions
- `init`: Initialize vector with x, y, z components
- `length`: Calculate vector magnitude
- `lengthSquared`: Calculate squared magnitude
- `normalize`: Convert to unit vector
- `equals`: Compare two vectors
- `printVector`: Debug output function

### Matrix3f Functions
- `rotateX/Y/Z`: Create rotation matrices
- `multiplyMatrixByVector`: Transform vectors
- `getMatrixRow/Column`: Extract matrix components
- `printMatrix`: Debug output function

## Applications of the Vector **Dot Product**

### 1. Vector Angle Calculation
The dot product is the angular relationship between two vectors using the formula:

`cos(θ) = (A · B) / (|A| * |B|)`

If `cos⁡(θ) > 0 (angle θ < 90°)`, the vectors point in a similar direction.

If `cos⁡(θ) = 0 (angle θ = 90°)`, the vectors are perpendicular.

If `cos⁡(θ) < 0 (angle θ > 90°)`, the vectors point in opposite directions.

---

### 2. Perpendicularity Detection
Vectors are **perpendicular** if their dot product equals zero:

`A · B = 0 ⇒ θ = 90°`

---

### 3. Vector Projection
The dot product is used to calculate the projection of one vector onto another:

`Projection of A onto B = (A · B) / |B|`

---

### 4. Parallelism Determination
Two vectors are **parallel** if:

`A · B = |A| |B|`

---

### 5. Computational Similarity Measurement
Machine Learning and data analysis, the dot product is used for:

- **Cosine similarity**: Quantifying similarity between vector representations.
- Measuring semantic proximity in word embeddings.
- Analysing directional correspondence in multidimensional spaces.

---

### 6. Graphics Lighting Computation
The dot product is fundamental in computer graphics for:

- Calculating the angle of light incidence on surfaces.
- Computing surface illumination intensities.
- Implementing lighting models such as **Phong shading** for diffuse lighting.

## Matrix Operations

| **Method** | **Purpose** | **Use Cases** | **Example** |
|------------|-------------|--------------|-------------|
| `Transpose` | Returns the transpose of a matrix | Switching coordinate systems, normal transformations in graphics, optimising dot products, basis transformations | Transpose of <br> ```[1  2]``` <br> ```[3  4]``` <br> is <br> ```[1  3]``` <br> ```[2  4]``` |
| `Determinant` | Computes the determinant of a matrix | Checking invertibility, finding areas/volumes in linear transformations, solving linear equations | Determinant of <br> ```[1  2]``` <br> ```[3  4]``` <br> is <br> `1(4) - 2(3) = -2` |
| `Inverse` | Returns the inverse of a matrix, if invertible | Solving systems of linear equations, applying transformations in graphics, undoing operations | Inverse of <br> ```[2  1]``` <br> ```[1  1]``` <br> is <br> ```[1  -1]``` <br> ```[-1  2]``` |


## Testing
The program includes a `test()` function that verifies:

- Vector initialization and length calculations
- Matrix rotation operations
- Vector-matrix multiplication accuracy

## Future Improvements
- Add more geometric primitives
- Implement color manipulation
- Add texture support
- Include more matrix operations
- Add camera controls

## Useful Resources
- [OpenGL](https://registry.khronos.org/OpenGL-Refpages/gl4/)
- [GLFW](https://www.glfw.org/)
- [Primitives](https://www.khronos.org/opengl/wiki/primitive)
- [Interactive Unit Circle](https://www.mathsisfun.com/algebra/trig-interactive-unit-circle.html)
- [Fixed Point Math Library for Rosco68k (Motorolla 68000)](https://bitbucket.org/MuddyGames/rosco_m68k_vr/src/main/include/math.h)

## Contact
For questions or support:

- muddygames