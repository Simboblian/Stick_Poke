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
#include "WorldObject.h"

#define FPS_DEFAULT 60.0f
#define WORLDTIME 1/60.0f
#define GRAVITY sf::Vector2f(0, 98.0f)
#define WINDOWSIZEX 1280
#define WINDOWSIZEY 768

class Engine
{
private:
	sf::Clock			*_deltaClock;

	sf::RenderWindow	*_window;

	b2World				*_b2World;
	SFMLDebugDraw		*_debugDraw;

	World				*_world;
	Player				*_player;
	Character			*_character;
	ObjectManager		*_objectManager;
	CollisionHandler	*_collisionHandler;

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