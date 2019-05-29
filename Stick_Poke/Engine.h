#ifndef _ENGINE_H
#define _ENGINE_H

#include <SFML/Graphics.hpp>
#include "World.h"
#include "Camera.h"
#include "Character.h"
#include "Player.h"
#include "ObjectManager.h"

#define FPS_DEFAULT 60.0f
#define GRAVITY sf::Vector2f(0, 9.8f)
#define WINDOWSIZEX 1280
#define WINDOWSIZEY 768

class Engine
{
private:
	sf::RenderWindow	*m_Window;

	World				*m_World;
	Camera				*m_Camera;
	Player				*m_Player;
	Character			*m_Character;
	ObjectManager		*m_ObjectManager;

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