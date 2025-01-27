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

    // glNewList(index, GL_COMPILE);
	// Creates a new Display List
	// Initalizes and Compiled to GPU
	// https://www.opengl.org/sdk/docs/man2/xhtml/glNewList.xml
	glNewList(game->index, GL_COMPILE);
	glBegin(GL_QUADS);
	{
		glColor3f(0.0f, 0.0f, 1.0f);
        // Define the vertices of the quad
        glVertex3f(-0.2f, -0.5f, 0.0f); // Bottom left
        glVertex3f(0.7f, -0.5f, 0.0f); // Bottom right
        glVertex3f(1.2f, 0.2f, 0.0f); // Top right
        glVertex3f(-0.7f, 0.2f, 0.0f); // Top left
	}

	glEnd();
	glEndList();


    game->index2 = glGenLists(1);        // Generate one display list
    glNewList(game->index2, GL_COMPILE);
    glBegin(GL_QUADS);
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-0.05f, -0.5f, 0.0f); // Bottom left
        glVertex3f(0.05f, -0.5f, 0.0f); // Bottom right
        glVertex3f(0.05f, 0.5f, 0.0f); // Top right
        glVertex3f(-0.05f, 0.5f, 0.0f); // Top left
    }
    glEnd();
    glEndList(); // End of display list compilation


    game->index3 = glGenLists(1);        // Generate one display list
    glNewList(game->index3, GL_COMPILE);
    glBegin(GL_TRIANGLES);
    {
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.125f, 1.67f, -5.0f); // Top vertex 
        glVertex3f(0.125f, 0.8f, -5.0f); // Bottom-left vertex 
        glVertex3f(1.0f, 1.2f, -5.0f); // Bottom-right vertex
        
    }
    glEnd();
    glEndList(); // End of display list compilation

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

    // Keep rotation angle between 0 and 360 degrees
    if (game->rotationAngle > 360.0f)
    {
        game->rotationAngle -= 360.0f;
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
    glTranslatef(-0.25f, -0.5f, -3.0f);
    //glRotatef(game->rotationAngle, 0, 0, 1);
    glCallList(game->index);                    // Draw cube using display list
    
    glLoadIdentity();                        // Reset the modelview matrix again for the second object
    glTranslatef(0.0f, 0.2f, -3.0f); 
    //glRotatef(game->rotationAngle, 0, 0, 1);// Apply a different translation for the second quad
    glCallList(game->index2);                // Draw the second quad

    glLoadIdentity();                        // Reset the modelview matrix again for the second object
    glTranslatef(0.0f, 0.2f, -3.0f); 
    //glRotatef(game->rotationAngle, 0, 0, 1);
    glCallList(game->index3);                // Draw the second quad

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
    glDeleteLists(game->index, 1); // Delete the display list
    glDeleteLists(game->index2, 1); // Delete the display list
    glDeleteLists(game->index3, 1); // Delete the display list
}