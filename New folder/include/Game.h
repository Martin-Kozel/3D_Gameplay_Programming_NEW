#include <iostream>

#include <GL/glew.h>

#include <./include/stb_image.h>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>


using namespace std;
using namespace sf;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void render();
	void unload();

	Clock clock;
	Time elapsed;
};