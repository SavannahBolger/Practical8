#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Vector3D.h"
#include "Matrix3.h"

using namespace std;
using namespace sf;
//using namespace gpp;

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
	bool flip = false;
	int current = 1;

	float rotationAngle = 0.0f;
};