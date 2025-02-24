#include <assert.h>

#include "./include/game.h"

// Global constants
const int SCREEN_WIDTH = 800;       // Screen Width
const int SCREEN_HEIGHT = 600;      // Screen Height
const float ROTATION_SPEED = 45.0f; // Degrees per second
const float FOV = 45.0f;            // Field of view in degrees
const float NEAR_PLANE = 1.0f;      // Near clipping plane for the camera
const float FAR_PLANE = 500.0f;     // Far clipping plane for the camera

// Test Method Vector and Matrix Operations
void test()
{
    // Create and initialize Vector3f objects
    Vector3f v1, v2, v3;

    initVector3f(&v1, 0.0f, 2.0f, -5.0f);
    DEBUG_MSG("Vector v1: ");
    printVector3f(&v1);
    printf("v1 length: %.7f\n\n", length(&v1));
    assert(fabs(length(&v1) - 5.3851647f) < 1e-7);

    initVector3f(&v2, -2.0f, -2.0f, -5.0f);
    DEBUG_MSG("Vector v2: ");
    printVector3f(&v2);
    printf("v2 length squared: %.7f\n", lengthSquared(&v2));
    assert(fabs(lengthSquared(&v2) - 33.0f) < 1e-7);

    initVector3f(&v3, 2.0f, -2.0f, -5.0f);
    DEBUG_MSG("Vector v3: ");
    printVector3f(&v3);

    // Rotate matrix by Z-axis
    Matrix3f rotationMatrix = rotateZ(23.21f);
    Vector3f rotatedV3 = multiplyMatrix3fByVector3f(&rotationMatrix, &v3);
    DEBUG_MSG("v3 rotated by 23.21 degrees around Z-axis: ");
    printVector3f(&rotatedV3);
    assert(fabs(rotatedV3.x - 2.6263378f) < 1e-7 && fabs(rotatedV3.y + 1.0499284f) < 1e-7);

    // Test with another rotation angle
    rotationMatrix = rotateZ(5.0f);
    rotatedV3 = multiplyMatrix3fByVector3f(&rotationMatrix, &v3);
    DEBUG_MSG("v3 rotated by 5 degrees around Z-axis: ");
    printVector3f(&rotatedV3);
    assert(fabs(rotatedV3.x - 2.1667008f) < 1e-7 && fabs(rotatedV3.y + 1.8180779f) < 1e-7);

    DEBUG_MSG("Quaternion about Z axis: Quaternion q(0.0f, 0.0f, 0.0f, 1.0f)");
    Quaternion q;
    initQuaternionValues(&q, 0.0f, 0.0f, 0.0f, 1.0f);

    DEBUG_MSG("v3f Quaternion rotated Z axis 23.21 degrees");
    Vector3f v3f;
    initVector3f(&v3f, 2.0f, -2.0f, -5.0f);
    Vector3f result = rotateVector3fByQuaternion(&q, &v3f, 23.21f);
    printf("Rotated v3f: x=%.7f, y=%.7f, z=%.7f\n", v3f.x, v3f.y, v3f.z);

    assert(result.x > 2.6263370f && result.x < 2.6263380f);
    assert(result.y < -1.0499280f && result.y > -1.0499290f);

    DEBUG_MSG("v3f Quaternion rotated Z axis 5.00 degrees");
    result = rotateVector3fByQuaternion(&q, &v3f, 5.0f);
    printf("Rotated v3f: x=%.7f, y=%.7f, z=%.7f\n", result.x, result.y, result.z);

    assert(result.x > 2.1667000f && result.x < 2.1667010f);
    assert(result.y < -1.8180770f && result.y > -1.8180780f);

    DEBUG_MSG("TODO: Complete all Math Library function tests");
}

/**
 * Initializes the game state and OpenGL settings
 * Sets up projection matrix, creates display lists, and initializes timing
 */
void initialize(Game *game)
{
    // Set background color to black (R=0, G=0, B=0, A=0)
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Setup perspective projection matrix
    glMatrixMode(GL_PROJECTION); // Switch to projection matrix mode
    glLoadIdentity();            // Reset projection matrix

    // Set up perspective: 45 Degrees field of view, 4:3 aspect ratio, near=1.0, far=500.0
    gluPerspective(FOV, SCREEN_WIDTH / SCREEN_HEIGHT, NEAR_PLANE, FAR_PLANE);
    glMatrixMode(GL_MODELVIEW); // Switch back to modelview matrix

    // Create a new display list for the cube
    game->index = glGenLists(1); // Generate one display list

    // Init Triangle
    // Set up the triangle vertices
    initVector3f(&game->triangle[0], 0.0f, 2.0f, -5.0f);
    initVector3f(&game->triangle[1], -2.0f, -2.0f, -5.0f);
    initVector3f(&game->triangle[2], 2.0f, -2.0f, -5.0f);

    DEBUG_MSG("Initial triangle vertices:\n");
    printVector3f(&game->triangle[0]);
    printVector3f(&game->triangle[1]);
    printVector3f(&game->triangle[2]);

    // glNewList(index, GL_COMPILE);
    // Creates a new Display List
    // Initalizes and Compiled to GPU
    // https://www.opengl.org/sdk/docs/man2/xhtml/glNewList.xml
    glNewList(game->index, GL_COMPILE);
    glBegin(GL_TRIANGLES);
    {
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(game->triangle[0].x, game->triangle[0].y, game->triangle[0].z);
        glVertex3f(game->triangle[1].x, game->triangle[1].y, game->triangle[1].z);
        glVertex3f(game->triangle[2].x, game->triangle[2].y, game->triangle[2].z);
    }

    glEnd();
    glEndList();

    // Initialize timing for animation
    game->lastTime = glfwGetTime();
}

/**
 * Handles Game Input
 */
void handleInput(GLFWwindow *window, Game *game)
{
    // Y-axis rotation (Left/Right arrows)
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        // Inside your input handling or update logic
        Matrix3f rotationMatrix = rotateZ(5.0f); // Rotate by 5 degrees

        game->triangle[0] = multiplyMatrix3fByVector3f(&rotationMatrix, &game->triangle[0]);
        game->triangle[1] = multiplyMatrix3fByVector3f(&rotationMatrix, &game->triangle[1]);
        game->triangle[2] = multiplyMatrix3fByVector3f(&rotationMatrix, &game->triangle[2]);

        // Debug output to check if the triangle is being rotated
        DEBUG_MSG("After rotation (anti-clockwise):\n");
        printVector3f(&game->triangle[0]);
        printVector3f(&game->triangle[1]);
        printVector3f(&game->triangle[2]);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        // Inside your input handling or update logic
        Matrix3f rotationMatrix = rotateZ(-5.0f); // Rotate by -5 degrees

        game->triangle[0] = multiplyMatrix3fByVector3f(&rotationMatrix, &game->triangle[0]);
        game->triangle[1] = multiplyMatrix3fByVector3f(&rotationMatrix, &game->triangle[1]);
        game->triangle[2] = multiplyMatrix3fByVector3f(&rotationMatrix, &game->triangle[2]);

        // Debug output to check if the triangle is being rotated
        DEBUG_MSG("After rotation (clockwise):\n");
        printVector3f(&game->triangle[0]);
        printVector3f(&game->triangle[1]);
        printVector3f(&game->triangle[2]);
    }

    // Recreate display list with updated triangle vertices
    glNewList(game->index, GL_COMPILE);
    glBegin(GL_TRIANGLES);
    {
        glColor3f(0.0f, 0.0f, 1.0f); // Blue color for triangle
        glVertex3f(game->triangle[0].x, game->triangle[0].y, game->triangle[0].z);
        glVertex3f(game->triangle[1].x, game->triangle[1].y, game->triangle[1].z);
        glVertex3f(game->triangle[2].x, game->triangle[2].y, game->triangle[2].z);
    }
    glEnd();
    glEndList();
}

/**
 * Updates game logic
 * Handles rotation timing and angle calculations
 */
void update(Game *game)
{
    // Get current time and calculate time elapsed
    double currentTime = glfwGetTime();

    // Update last time
    game->lastTime = currentTime;

    static double lastLogTime = 0.0;
    if (currentTime - lastLogTime >= 1.0)
    {
        DEBUG_MSG("Triangle vertices:\n");
        printVector3f(&game->triangle[0]);
        printVector3f(&game->triangle[1]);
        printVector3f(&game->triangle[2]);
        lastLogTime = currentTime;
    }
}

/**
 * Renders the scene
 * Clears buffers, applies transformations, and draws the cube
 */
void draw(Game *game)
{
    // Get current time and calculate time elapsed
    double currentTime = glfwGetTime();

    // Clear color and depth buffers for new frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update last time
    game->lastTime = currentTime;

    static double lastLogTime = 0.0;
    if (currentTime - lastLogTime >= 1.0)
    {
        DEBUG_MSG("Drawing Primative\n");
        lastLogTime = currentTime;
    }

    glLoadIdentity();        // Reset modelview matrix
    glCallList(game->index); // Draw cube using display list

    // Swap front and back buffers to display the rendered frame
    glfwSwapBuffers(game->window);
}

/**
 * Main game loop
 * Initializes GLFW, creates window, and runs the game loop
 */
void run(Game *game)
{
    // Initialize GLFW library
    if (!glfwInit())
    {
        DEBUG_MSG("Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    // Create a windowed mode window and its OpenGL context
    game->window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GLFW OpenGL Triangle StarterKit with 3D Math Library", NULL, NULL);
    if (!game->window)
    {
        glfwTerminate();
        DEBUG_MSG("Failed to create GLFW window\n");
        exit(EXIT_FAILURE);
    }

    // Make the window's context current
    glfwMakeContextCurrent(game->window);

    // Initialize game state and OpenGL settings
    initialize(game);

    // Test methods
    test();

    // Main game loop
    while (!glfwWindowShouldClose(game->window))
    {
        handleInput(game->window, game); // Handle game input
        update(game);                    // Update game logic
        draw(game);                      // Render frame
        glfwPollEvents();                // Process window events
    }

    // Cleanup resources
    destroy(game);
    glfwDestroyWindow(game->window);
    glfwTerminate();
}

/**
 * Cleanup function
 * Releases allocated resources
 */
void destroy(Game *game)
{
    DEBUG_MSG("Cleaning up\n");
    glDeleteLists(game->index, 1); // Delete the display list
}