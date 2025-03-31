#include <./include/Debug.h>
#include <./include/Game.h>

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube Texturing")
{
}

Game::~Game() {}

void Game::run()
{
    initialize();

    Event event;

    while (isRunning)
    {
#if (DEBUG >= 2)
        DEBUG_MSG("Game running...");
#endif

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                isRunning = false;
            }
        }
        update();
        render();
    }
}

typedef struct
{
    float coordinate[3];
    float color[4];
    float texel[2];
} Vertex;

Vertex vertex[36];  // Cube has 36 vertices (6 faces with 6 vertices each)
GLubyte triangles[36];  // Indices for 6 faces

GLuint index,    // Index to draw
vsid,         // Vertex Shader ID
fsid,         // Fragment Shader ID
progID,       // Program ID
vbo = 1,      // Vertex Buffer ID
positionID,   // Position ID
colorID,      // Color ID
texelID,      // Texel ID
textureID;    // Texture ID

const string filename = "./assets/texture.tga";

int width;               // width of texture
int height;              // height of texture
int comp_count;          // Component of texture
const int number = 4;    // 4 = RGBA

unsigned char* img_data;

void Game::initialize()
{
    isRunning = true;

    GLint isCompiled = 0;
    GLint isLinked = 0;

    glewInit();

    for (int i = 0; i < 36; ++i)
    {
        vertex[i].color[0] = 1.0f;
        vertex[i].color[1] = 1.0f;
        vertex[i].color[2] = 1.0f;
        vertex[i].color[3] = 1.0f;

        vertex[i].texel[0] = (i % 2) == 0 ? 0.0f : 1.0f;  // Alternate texel coordinates
        vertex[i].texel[1] = (i % 3) == 0 ? 0.0f : 1.0f;
    }

    // Cube vertex positions
    float cubeVertices[36][3] = {
        // Front face
        {-0.5f, -0.5f,  0.5f}, { 0.5f, -0.5f,  0.5f}, { 0.5f,  0.5f,  0.5f},
        {-0.5f, -0.5f,  0.5f}, { 0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f},
        // Back face
        {-0.5f, -0.5f, -0.5f}, {-0.5f,  0.5f, -0.5f}, { 0.5f,  0.5f, -0.5f},
        {-0.5f, -0.5f, -0.5f}, { 0.5f,  0.5f, -0.5f}, { 0.5f, -0.5f, -0.5f},
        // Left face
        {-0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f},
        {-0.5f, -0.5f, -0.5f}, {-0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f, -0.5f},
        // Right face
        { 0.5f, -0.5f, -0.5f}, { 0.5f,  0.5f, -0.5f}, { 0.5f,  0.5f,  0.5f},
        { 0.5f, -0.5f, -0.5f}, { 0.5f,  0.5f,  0.5f}, { 0.5f, -0.5f,  0.5f},
        // Top face
        {-0.5f,  0.5f, -0.5f}, {-0.5f,  0.5f,  0.5f}, { 0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f, -0.5f}, { 0.5f,  0.5f,  0.5f}, { 0.5f,  0.5f, -0.5f},
        // Bottom face
        {-0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f,  0.5f},
        {-0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f,  0.5f}, {-0.5f, -0.5f,  0.5f}
    };

    // Assign cube positions to vertices
    for (int i = 0; i < 36; ++i)
    {
        vertex[i].coordinate[0] = cubeVertices[i][0];
        vertex[i].coordinate[1] = cubeVertices[i][1];
        vertex[i].coordinate[2] = cubeVertices[i][2];
    }

    // Indices for drawing the cube (6 faces with 2 triangles each, 3 indices per triangle)
    GLubyte cubeIndices[36] = {
        0, 1, 2, 0, 2, 3,  // Front face
        4, 5, 6, 4, 6, 7,  // Back face
        8, 9, 10, 8, 10, 11, // Left face
        12, 13, 14, 12, 14, 15, // Right face
        16, 17, 18, 16, 18, 19, // Top face
        20, 21, 22, 20, 22, 23  // Bottom face
    };

    // Copy indices to the triangle array
    for (int i = 0; i < 36; ++i)
    {
        triangles[i] = cubeIndices[i];
    }

    // Create a new VBO using VBO id
    glGenBuffers(1, &vbo);

    // Bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Upload vertex data to GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Vertex Shader
    const char* vs_src = "#version 400\n\r"
        "in vec4 sv_position;"
        "in vec4 sv_color;"
        "in vec2 sv_texel;"
        "out vec4 color;"
        "out vec2 texel;"
        "void main() {"
        "    color = sv_color;"
        "    texel = sv_texel;"
        "    gl_Position = sv_position;"
        "}";

    vsid = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL);
    glCompileShader(vsid);
    glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
    }

    // Fragment Shader
    const char* fs_src = "#version 400\n\r"
        "uniform sampler2D f_texture;"
        "in vec4 color;"
        "in vec2 texel;"
        "out vec4 fColor;"
        "void main() {"
        "    fColor = texture(f_texture, texel.st);"
        "}";

    fsid = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
    glCompileShader(fsid);
    glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
    }

    // Link Shader
    progID = glCreateProgram();
    glAttachShader(progID, vsid);
    glAttachShader(progID, fsid);
    glLinkProgram(progID);
    glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        DEBUG_MSG("ERROR: Shader Link Error");
    }

    glUseProgram(progID);

    // Setup the Texture Data and send to GPU
    img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 4);
    if (img_data == NULL) {
        DEBUG_MSG("ERROR: Texture not loaded");
    }

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);

    positionID = glGetAttribLocation(progID, "sv_position");
    colorID = glGetAttribLocation(progID, "sv_color");
    texelID = glGetAttribLocation(progID, "sv_texel");
    textureID = glGetUniformLocation(progID, "f_texture");
}

void Game::update()
{
    elapsed = clock.getElapsedTime();
}

void Game::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);

    glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (float*)NULL + 3);

    glEnableVertexAttribArray(positionID);
    glEnableVertexAttribArray(colorID);
    glEnableVertexAttribArray(texelID);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

    window.display();
}

void Game::unload()
{
    cout << "Cleaning up" << endl;
    glDeleteProgram(progID);
    glDeleteBuffers(1, &vbo);
}
