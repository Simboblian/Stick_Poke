#ifndef _ENGINE_H
#define _ENGINE_H

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>"
#include "SFMLDebugDraw.h"
#include "World\World.h"
#include "Camera\Camera.h"
#include "Objects\Character.h"

#define FPS_DEFAULT 60.0f
#define SCALE 32.0f
#define GRAVITY 9.8f
#define WINDOWSIZEX 1920
#define WINDOWSIZEY 1080

using namespace sf;

class Engine
{
private:
	RenderWindow* m_Window;

	b2World* m_B2World;
	SFMLDebugDraw* m_DebugDraw;

	World* m_World;
	Camera* m_Camera;
	Character* m_Character;

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