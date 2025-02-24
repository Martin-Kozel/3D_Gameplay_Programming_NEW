#ifndef GAME_H
#define GAME_H

// Windows-specific definitions
#ifdef _WIN32
    #define CALLBACK __stdcall
#endif

#include <GLFW/glfw3.h> // GLFW for window management and OpenGL context
#include <GL/gl.h>      // OpenGL core functionality
#include <GL/glu.h>     // OpenGL Utility Library for perspective projection
#include <stdio.h>      // Standard I/O operations
#include <stdlib.h>     // Standard library functions
#include <stdbool.h>    // Boolean type support

#include "./include/debug.h"

#include "./include/vector3f.h"
#include "./include/matrix3f.h"
#include "./include/quaternion.h"

// Game state structure to maintain all necessary game data
typedef struct Game
{
    GLFWwindow *window;  // Pointer to GLFW window
    GLuint index;        // Display list index for cube geometry
    double lastTime;     // Time tracking for animation
    Vector3f triangle[3];// Triangle data in 3D space
} Game;

// Function prototypes for game lifecycle management
void initialize(Game *game);                      // Initialize game state and OpenGL
void handleInput(GLFWwindow *window, Game *game); // Handle player input
void update(Game *game);                          // Update game logic
void draw(Game *game);                            // Render the scene
void run(Game *game);                             // Main game loop
void destroy(Game *game);                         // Cleanup resources

#endif // GAME_H