#include <iostream>
#include <SFML\Graphics.hpp>
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
	void movement();
	void unload();

	Clock clock;
	Time elapsed;
	bool flip = false;
	int current = 1;
	Vector3D activeTranslation{ 0,-1,0 };
	Vector3D originalPosition[8] = { {-30,0,0},{ -30,15,0 },{ 30,0,0 },{ 30,-15,0 },{ -30,0,-30 },{ -30,15,-30 },{ 30,0,-30 },{ 30,-15,-30 } };
	Vector3D position[8];
	Vector3D currentPosition[8];
	Matrix3 xRotation;//x axis rotation
	Matrix3 yRotation;//y axis rotation
	Matrix3 zRotation;//z axis rotation
	float rotationAngle = 0.0f;
};