#ifndef _ENGINE_H
#define _ENGINE_H

#include <SFML\Graphics.hpp>

#define FPS_DEFAULT 60.0f

class Engine
{
private:
	sf::RenderWindow* window;

	bool Init();
	void MainLoop();
	void RenderFrame();
	void ProcessInput();
	void Update();
public:
	void Go();

	Engine();
	~Engine();
};


#endif