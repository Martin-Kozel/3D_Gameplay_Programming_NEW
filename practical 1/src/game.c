#include <./include/game.h>

// Global flag to control update state
bool updatable = false;

// Global constants
const int SCREEN_WIDTH = 800;       // Screen Width
const int SCREEN_HEIGHT = 600;      // Screen Height
const float ROTATION_SPEED = 45.0f; // Degrees per second
const float FOV = 45.0f;            // Field of view in degrees
const float NEAR_PLANE = 1.0f;      // Near clipping plane for the camera
const float FAR_PLANE = 500.0f;     // Far clipping plane for the camera

/**
 * Initializes the game state and OpenGL settings
 * Sets up projection matrix, creates display lists, and initializes timing
 */
void initialize(Game *game)
{
    // Set initial game state
    game->isRunning = 1;
    game->rotationAngle = 0.0f; 
    game->rotationAngleZ = 0.0f;
    game->scaleFactor = 1.0f;   

    // Set background color to black (R=0, G=0, B=0, A=0)
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Setup perspective projection matrix
    glMatrixMode(GL_PROJECTION); // Switch to projection matrix mode
    glLoadIdentity();            // Reset projection matrix

    // Set up perspective: 45 Degrees field of view, 4:3 aspect ratio, near=1.0, far=500.0
    gluPerspective(FOV, SCREEN_WIDTH / SCREEN_HEIGHT, NEAR_PLANE, FAR_PLANE);
    glMatrixMode(GL_MODELVIEW); // Switch back to modelview matrix

    // Create a new display list for the cube
    game->index = glGenLists(1);        // Generate one display list
    glNewList(game->index, GL_COMPILE); // Start recording display list

    // Begin defining cube geometry using quads
    glBegin(GL_QUADS);
    {
        // Front face of cube (Blue)
        glColor3f(0.0f, 0.0f, 1.0f);     // Set color to blue
        glVertex3f(1.0f, 1.0f, -5.0f);   // Top-right vertex V1
        glVertex3f(-1.0f, 1.0f, -5.0f);  // Top-left vertex V0
        glVertex3f(-1.0f, -1.0f, -5.0f); // Bottom-left vertex V3
        glVertex3f(1.0f, -1.0f, -5.0f);  // Bottom-right vertex V2

        // Back face of cube (Green)
        glColor3f(0.0f, 1.0f, 0.0f);      // Set color to green 
        glVertex3f(1.0f, 1.0f, -15.0f);   // Top-right vertex V5
        glVertex3f(-1.0f, 1.0f, -15.0f);  // Top-left vertex V4
        glVertex3f(-1.0f, -1.0f, -15.0f); // Bottom-left vertex V7
        glVertex3f(1.0f, -1.0f, -15.0f);  // Bottom-right vertex V6

        // Right side of cube (Pink)
        glColor3f(1.0f, 0.0f, 1.0f);     // Set color to pink
        glVertex3f(1.0f, 1.0f, -15.0f);   // Top-right vertex v5
        glVertex3f(1.0f, 1.0f, -5.0f);   // Top-left vertex V1
        glVertex3f(1.0f, -1.0f, -5.0f);  // Bottom-left vertex V2
        glVertex3f(1.0f, -1.0f, -15.0f);  // Bottom-right vertex v6

        // Left side of cube (White)
        glColor3f(1.0f, 1.0f, 1.0f);     // Set color to white
        glVertex3f(-1.0f, 1.0f, -5.0f);  // Top-right vertex V0
        glVertex3f(-1.0f, 1.0f, -15.0f);  // Top-left vertex v4
        glVertex3f(-1.0f, -1.0f, -15.0f); // Bottom-left vertex v7
        glVertex3f(-1.0f, -1.0f, -5.0f);    // Bottom-right vertex V3

         // Bottom side of cube (Yellow)
        glColor3f(1.0f, 1.0f, 0.0f); // Set color to yellow
        glVertex3f(1.0f, -1.0f, -5.0f);  // Top Right vertex V2
        glVertex3f(-1.0f, -1.0f, -5.0f); // Top Left vertex V3
        glVertex3f(-1.0f, -1.0f, -15.0f); // Bottom-left vertex V7
        glVertex3f(1.0f, -1.0f, -15.0f);  // Bottom-right vertex v6


    }
    glEnd();     // End geometry definition
    glEndList(); // End display list compilation

    // Initialize timing for animation
    game->lastTime = glfwGetTime();
}

/**
 * Handles Game Input
 */
void handleInput(GLFWwindow *window, Game *game)
{
    // Get current time and calculate time elapsed
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - game->lastTime;

    // Y-axis rotation (Left/Right arrows)
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        // Update rotation continuously using deltaTime
        game->rotationAngle += ROTATION_SPEED * deltaTime; // 45 degrees per second
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        // Update rotation continuously using deltaTime
        game->rotationAngle -= ROTATION_SPEED * deltaTime; // 45 degrees per second
    }
    
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        // Update rotation continuously using deltaTime
        game->rotationAngleZ += ROTATION_SPEED * deltaTime; // 45 degrees per second
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        // Update rotation continuously using deltaTime
        game->rotationAngleZ -= ROTATION_SPEED * deltaTime; // 45 degrees per second
    }

    if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
    {
        game->scaleFactor += 0.01f;
        if (game->scaleFactor > 2.0f) game->scaleFactor = 2.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
    {
        game->scaleFactor -= 0.01f;
        if (game->scaleFactor < 0.1f) game->scaleFactor = 0.1f;
    }

    // Keep rotation angle between 0 and 360 degrees
    if (game->rotationAngle > 360.0f)
    {
        game->rotationAngle -= 360.0f;
    }

    // Keep rotation angle between 0 and 360 degrees
    if (game->rotationAngleZ > 360.0f)
    {
        game->rotationAngleZ -= 360.0f;
    }
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
        printf("Update : rotationAngle = %.2f\n", game->rotationAngle);
        printf("Update : rotationAngleZ = %.2f\n", game->rotationAngleZ);
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
        printf("Drawing Cube\n");
        lastLogTime = currentTime;
    }

    glLoadIdentity();                        // Reset modelview matrix

    //glRotatef(game->rotationAngle, 0, 1, 1); // Apply rotation around Y and Z axis
    glRotatef(game->rotationAngle, 0, 1, 0);  // Rotate around Y-axis
    glRotatef(game->rotationAngleZ, 0, 0, 1); // Rotate around Z-axis

    glTranslatef(0.0f, 0.0f, -5.0f);         // Push it closer or further

    glScalef(game->scaleFactor, game->scaleFactor, game->scaleFactor);

    glCallList(game->index);                // Draw cube using display list

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
        printf("Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    // Create a windowed mode window and its OpenGL context
    game->window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GLFW OpenGL Cube", NULL, NULL);
    if (!game->window)
    {
        glfwTerminate();
        printf("Failed to create GLFW window\n");
        exit(EXIT_FAILURE);
    }

    // Make the window's context current
    glfwMakeContextCurrent(game->window);

    // Initialize game state and OpenGL settings
    initialize(game);

    // Main game loop
    while (!glfwWindowShouldClose(game->window))
    {
        handleInput(game->window, game); // Handle game input
        update(game);                    // Update game logic
        draw(game);                      // Render frame
        glfwPollEvents();                 // Process window events
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
    printf("Cleaning up\n");
    glDeleteLists(game->index, 1); // Delete the display list
}
