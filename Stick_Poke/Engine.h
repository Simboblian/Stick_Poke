#ifndef _ENGINE_H
#define _ENGINE_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "SFMLDebugDraw.h"
#include "World.h"
#include "Character.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Utility.h"
#include "CollisionHandler.h"

#define FPS_DEFAULT 60.0f
#define WORLDTIME 1/60.0f
#define GRAVITY sf::Vector2f(0, 98.0f)
#define WINDOWSIZEX 1280
#define WINDOWSIZEY 768

class Engine
{
private:
	sf::RenderWindow	*m_Window;

	b2World				*m_B2World;
	SFMLDebugDraw		*m_DebugDraw;

	World				*m_World;
	Player				*m_Player;
	Character			*m_Character;
	ObjectManager		*m_ObjectManager;
	CollisionHandler	*m_CollisionHandler;

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