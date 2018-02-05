#include "Game.h"

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube")
{
	for (size_t i = 0; i < 8; i++)
	{
		currentPosition[i] = originalPosition[i];
	}
}

Game::~Game() {}

float vertices[] = { 
	1.0f, 1.0f, -5.0f, -1.0f, 1.0f, -5.0f,-1.0f, -1.0f, -5.0f,
	1.0f, 1.0f, -5.0f, -1.0f, -1.0f, -5.0f,1.0f, -1.0f, -5.0f,
	1.0f, -1.0f, -5.0f,-1.0f, -1.0f, -5.0f,-1.0f, -1.0f, -7.0f,
	1.0f, -1.0f, -5.0f, -1.0f, -1.0f, -7.0f, 1.0f, -1.0f, -7.0f,
	1.0f, -1.0f, -7.0f, -1.0f, -1.0f, -7.0f, -1.0f, 1.0f, -7.0f,
	1.0f, -1.0f, -7.0f, -1.0f, -1.0f, -7.0f, 1.0f, 1.0f, -7.0f,
	1.0f, 1.0f, -7.0f, -1.0f, 1.0f, -7.0f, -1.0f, 1.0f, -5.0f,
	1.0f, 1.0f, -7.0f, -1.0f, 1.0f, -5.0f, 1.0f, 1.0f, -5.0f,
	-1.0f, 1.0f, -5.0f, -1.0f, 1.0f, -7.0f, -1.0f, -1.0f, -7.0f,
	-1.0f, 1.0f, -5.0f, -1.0f, -1.0f, -7.0f,  -1.0f, -1.0f, -5.0f,
	1.0f, 1.0f, -7.0f,  1.0f, 1.0f, -5.0f,  1.0f, -1.0f, -5.0f, 
	1.0f, 1.0f, -7.0f,  1.0f, -1.0f, -5.0f,  1.0f, -1.0f, -7.0f };

float colors[] = { 
	1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };

unsigned int vertex_index[] = { 
	0, 1, 2, 
	3, 4, 5,
	6, 7,8,
	9,10,11,
	12,13,14,
	15,16,17,
	18,19,20,
	21,22,23,
	24,25,26,
	27,28,29,
	30,31,32,
	33,34,35 };

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

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

void Game::initialize()
{
	isRunning = true;
	
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();
	movement();
	
	for (size_t i = 0; i < 8; i++)
	{
		position[i] = Vector3D((currentPosition[i].X() + 400) * window.getSize().x / window.getSize().y, (currentPosition[i].Y() + 300) * window.getSize().x / window.getSize().y, (currentPosition[i].Z()) * window.getSize().x / window.getSize().y);
	}
	for (size_t i = 0; i < 36; i+=3)
	{
		vertices[i] = position[i].X()* window.getSize().x / window.getSize().y;
		vertices[i+1] = position[i].Y()* window.getSize().x / window.getSize().y;
		vertices[i+2] = position[i].Z()* window.getSize().x / window.getSize().y;
	}
	cout << "Update up" << endl;
}

void Game::render()
{
	cout << "Drawing" << endl;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glVertexPointer(3, GL_FLOAT, 0, &vertices);
	glColorPointer(3, GL_FLOAT, 0, &colors);
	glVertexPointer(6, GL_FLOAT, 3, &vertices);
	glColorPointer(6, GL_FLOAT, 3, &colors);
	glVertexPointer(9, GL_FLOAT, 3, &vertices);
	glColorPointer(9, GL_FLOAT, 3, &colors);
	glVertexPointer(12, GL_FLOAT, 3, &vertices);
	glColorPointer(12, GL_FLOAT, 3, &colors);
	glVertexPointer(15, GL_FLOAT, 3, &vertices);
	glColorPointer(15, GL_FLOAT, 3, &colors);
	glVertexPointer(18, GL_FLOAT, 3, &vertices);
	glColorPointer(18, GL_FLOAT, 3, &colors);
	glVertexPointer(21, GL_FLOAT, 3, &vertices);
	glColorPointer(21, GL_FLOAT, 3, &colors);
	glVertexPointer(24, GL_FLOAT, 3, &vertices);
	glColorPointer(24, GL_FLOAT, 3, &colors);
	glVertexPointer(27, GL_FLOAT, 3, &vertices);
	glColorPointer(27, GL_FLOAT, 3, &colors);
	glVertexPointer(30, GL_FLOAT, 3, &vertices);
	glColorPointer(30, GL_FLOAT, 3, &colors);
	glVertexPointer(33, GL_FLOAT, 3, &vertices);
	glColorPointer(33, GL_FLOAT, 3, &colors);
	glVertexPointer(36, GL_FLOAT, 3, &vertices);
	glColorPointer(36, GL_FLOAT, 3, &colors);

	glDrawArrays(GL_TRIANGLES, 0, 108);

	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, &vertex_index);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	window.display();

}

void Game::movement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			xRotation = Matrix3::rotationX(0.00174533);//angle set to 2 degrees
			for (size_t i = 0; i < 8; i++)
			{
				currentPosition[i] = xRotation * currentPosition[i];

			}
			//glRotatef(rotationAngle, 1, 0, 0); // Rotates the camera on Y Axis
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			yRotation = Matrix3::rotationY(0.00174533);//angle set to 2 degrees
			for (size_t i = 0; i < 8; i++)
			{
				currentPosition[i] = yRotation * currentPosition[i];

			}
			//glRotatef(rotationAngle, 0, 1, 0); // Rotates the camera on Y Axis

		}
		
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			zRotation = Matrix3::rotationZ(0.00174533);//angle set to 2 degrees
			for (size_t i = 0; i < 8; i++)
			{
				currentPosition[i] = zRotation * currentPosition[i];

			}
			//glRotatef(rotationAngle, 0, 0, 1); // Rotates the camera on Y Axis
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			for (size_t i = 0; i < 8; i++)
			{
				currentPosition[i] = (Matrix3::translation(activeTranslation) * originalPosition[i]) - Vector3D(0, 1, 0);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			for (size_t i = 0; i < 8; i++)
			{
				currentPosition[i] = (Matrix3::translation(activeTranslation) * originalPosition[i]) + Vector3D(0, 1, 0);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			//currentPosition[i] = (Matrix3::translation(activeTranslation) * originalPosition[i]) - Vector3D(1, 0, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			//currentPosition[i] = (Matrix3::translation(activeTranslation) * currentPosition[i]) + Vector3D(1, 0, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			//originalPosition[i] = (Matrix3::scale(1.5) * originalPosition[i]);
		}
		else
		{
			for (size_t i = 0; i < 8; i++)
			{
				currentPosition[i] = originalPosition[i];
			}
		}
	
}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

