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

// Define vertex positions for a Pyramid
// Format: X, Y, Z coordinates for each vertex
float vertices[] = {
    // Base vertices (forms a square at Y = -1)
    -1.0f, -1.0f, -5.0f,  // Vertex 0: Base front-left
     1.0f, -1.0f, -5.0f,  // Vertex 1: Base front-right
     1.0f, -1.0f, -3.0f,  // Vertex 2: Base back-right
    -1.0f, -1.0f, -3.0f,  // Vertex 3: Base back-left
    // Apex vertex
     0.0f,  1.0f, -4.0f   // Vertex 4: Top point (centered)
};

// Cube indices for 12 triangles (2 triangles per face)
GLfloat cubeVertices[] = {
    // Front face
    -0.5f, -0.5f,  0.5f,  // Bottom-left
     0.5f, -0.5f,  0.5f,  // Bottom-right
     0.5f,  0.5f,  0.5f,  // Top-right
    -0.5f,  0.5f,  0.5f,  // Top-left
    // Back face
    -0.5f, -0.5f, -0.5f,  // Bottom-left
     0.5f, -0.5f, -0.5f,  // Bottom-right
     0.5f,  0.5f, -0.5f,  // Top-right
    -0.5f,  0.5f, -0.5f,  // Top-left
    // Left face
    -0.5f, -0.5f, -0.5f,  // Bottom-left
    -0.5f, -0.5f,  0.5f,  // Bottom-right
    -0.5f,  0.5f,  0.5f,  // Top-right
    -0.5f,  0.5f, -0.5f,  // Top-left
    // Right face
     0.5f, -0.5f, -0.5f,  // Bottom-left
     0.5f, -0.5f,  0.5f,  // Bottom-right
     0.5f,  0.5f,  0.5f,  // Top-right
     0.5f,  0.5f, -0.5f,  // Top-left
    // Top face
    -0.5f,  0.5f, -0.5f,  // Bottom-left
     0.5f,  0.5f, -0.5f,  // Bottom-right
     0.5f,  0.5f,  0.5f,  // Top-right
    -0.5f,  0.5f,  0.5f,  // Top-left
    // Bottom face
    -0.5f, -0.5f, -0.5f,  // Bottom-left
     0.5f, -0.5f, -0.5f,  // Bottom-right
     0.5f, -0.5f,  0.5f,  // Top-right
    -0.5f, -0.5f,  0.5f   // Top-left
};


// Define colors for each vertex
// Format: R, G, B values for each vertex
float colors[] = {
    0.0f, 1.0f, 0.0f,  // Vertex 0: Bright green
    0.2f, 0.8f, 0.2f,  // Vertex 1: Light green
    0.0f, 0.5f, 0.0f,  // Vertex 2: Medium green
    0.0f, 0.3f, 0.0f,  // Vertex 3: Dark green
    1.0f, 0.0f, 0.0f   // Vertex 4: Red (apex)
};

GLfloat cubeColors[] = {
    // Front face (Red)
    1.0f, 0.0f, 0.0f, // Red
    1.0f, 0.0f, 0.0f, // Red
    1.0f, 0.0f, 0.0f, // Red
    1.0f, 0.0f, 0.0f, // Red

    // Back face (Green)
    0.0f, 1.0f, 0.0f, // Green
    0.0f, 1.0f, 0.0f, // Green
    0.0f, 1.0f, 0.0f, // Green
    0.0f, 1.0f, 0.0f, // Green

    // Left face (Blue)
    0.0f, 0.0f, 1.0f, // Blue
    0.0f, 0.0f, 1.0f, // Blue
    0.0f, 0.0f, 1.0f, // Blue
    0.0f, 0.0f, 1.0f, // Blue

    // Right face (Yellow)
    1.0f, 1.0f, 0.0f, // Yellow
    1.0f, 1.0f, 0.0f, // Yellow
    1.0f, 1.0f, 0.0f, // Yellow
    1.0f, 1.0f, 0.0f, // Yellow

    // Top face (Magenta)
    1.0f, 0.0f, 1.0f, // Magenta
    1.0f, 0.0f, 1.0f, // Magenta
    1.0f, 0.0f, 1.0f, // Magenta
    1.0f, 0.0f, 1.0f, // Magenta

    // Bottom face (Cyan)
    0.0f, 1.0f, 1.0f, // Cyan
    0.0f, 1.0f, 1.0f, // Cyan
    0.0f, 1.0f, 1.0f, // Cyan
    0.0f, 1.0f, 1.0f  // Cyan
};


// Define indices to connect vertices into triangles
// Format: Groups of 3 indices that define each triangle
unsigned int indices[] = {
    // Base triangles (clockwise order)
    0, 1, 2,  // Base triangle 1
    0, 2, 3,  // Base triangle 2
    
    // Side triangles (all share the apex vertex 4)
    0, 1, 4,  // Front face
    1, 2, 4,  // Right face
    2, 3, 4,  // Back face
    3, 0, 4,   // Left face

    // Left face
    8, 9, 10,
    8, 10, 11,

    // Right face
    12, 13, 14,
    12, 14, 15,

    // Top face
    16, 17, 18,
    16, 18, 19,

    // Bottom face
    20, 21, 22,
    20, 22, 23
};

/**
 * Initializes the game state and OpenGL settings
 * Sets up projection matrix, creates display lists, and initializes timing
 */
void initialize(Game *game)
{
    // Set initial game state
    game->isRunning = 1;

    // Set background color to black (R=0, G=0, B=0, A=0)
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Setup view perspective projection matrix
    glMatrixMode(GL_PROJECTION); // Switch to projection matrix mode
    glLoadIdentity();            // Reset projection matrix

    // Set up perspective: 45 Degrees field of view, 4:3 aspect ratio, near=1.0, far=500.0
    gluPerspective(FOV, SCREEN_WIDTH / SCREEN_HEIGHT, NEAR_PLANE, FAR_PLANE);
    glMatrixMode(GL_MODELVIEW); // Switch back to modelview matrix

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
        game->rotationY += ROTATION_SPEED * deltaTime; // 45 degrees per second
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        // Update rotation continuously using deltaTime
        game->rotationY -= ROTATION_SPEED * deltaTime; // 45 degrees per second
    }

    // X-axis rotation (Up/Down arrows)
    // Add up/down rotation
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        game->rotationX += ROTATION_SPEED * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        game->rotationX -= ROTATION_SPEED * deltaTime;
    }

    // Keep rotations between 0 and 360 degrees
    if (game->rotationY > 360.0f)
        game->rotationY -= 360.0f;
    if (game->rotationY < 0.0f)
        game->rotationY += 360.0f;
    if (game->rotationX > 360.0f)
        game->rotationX -= 360.0f;
    if (game->rotationX < 0.0f)
        game->rotationX += 360.0f;
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
        printf("Update : rotationY = %.2f\n", game->rotationY);
        lastLogTime = currentTime;
    }
}

/**
 * Renders the scene
 * Clears buffers, applies transformations, and draws the Vertex Array
 */
void draw(Game *game)
{
    // Clear color and depth buffers for new frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Get current time and calculate time elapsed
    double currentTime = glfwGetTime();

    // Update last time
    game->lastTime = currentTime;

    static double lastLogTime = 0.0;
    if (currentTime - lastLogTime >= 1.0)
    {
        printf("Drawing Model\n");
        lastLogTime = currentTime;
    }

    // Reset modelview matrix before applying transformations
    glLoadIdentity();

    // Move the model to visible position
    glTranslatef(0.0f, 0.0f, -4.0f);

    // Apply rotations
    glRotatef(game->rotationX, 1.0f, 0.0f, 0.0f); // Rotate around X axis
    glRotatef(game->rotationY, 0.0f, 1.0f, 0.0f); // Rotate around Y axis

    // Enable vertex and color arrays
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    // Set up vertex and color pointers
    glVertexPointer(3, GL_FLOAT, 0, &vertices);
    glColorPointer(3, GL_FLOAT, 0, &colors);

    // Draw the pyramid using indices
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, &indices);

    // Disable vertex and color arrays
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

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
    game->window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GLFW OpenGL VBA Vertex Arrays", NULL, NULL);
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
    printf("Cleaning up\n");
    (void)game; // Unused
}