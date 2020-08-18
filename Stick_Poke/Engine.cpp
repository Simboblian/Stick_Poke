#include "Engine.h"

void Engine::Go()
{
	if (!Init())
		throw "Could not initialise Engine";

	MainLoop();
}

void Engine::MainLoop()
{
	_deltaClock = new sf::Clock();

	while(_window->isOpen())
	{
		ProcessInput();

		Update();

		RenderFrame();
	}
}

// Initialization of the ENGINE
bool Engine::Init()
{
	bool passInit = true;
	_deltaClock = new sf::Clock();

	_window = new sf::RenderWindow(sf::VideoMode(WINDOWSIZEX, WINDOWSIZEY), "Stick Poke"/*, sf::Style::Fullscreen*/);
	_window->setFramerateLimit(FPS_DEFAULT);
	_window->setMouseCursorGrabbed(true);
	_window->setMouseCursorVisible(false);

	if (!_window)
		passInit = false;

	_b2World = new b2World(Utility::SFVECtoB2VEC(GRAVITY, false));

	_debugDraw = new SFMLDebugDraw(*_window);
	uint32 _flags = 0;
	//_flags += b2Draw::e_aabbBit;
	//_flags += b2Draw::e_centerOfMassBit;
	//_flags += b2Draw::e_pairBit;
	//_flags += b2Draw::e_jointBit;
	_flags += b2Draw::e_shapeBit;
	_debugDraw->SetFlags(_flags);

	_b2World->SetDebugDraw(_debugDraw);

	_objectManager = new ObjectManager();

	_collisionHandler = new CollisionHandler(*_objectManager);
	_b2World->SetContactListener(_collisionHandler);


	//Create the world and add it's objects to the game;
	_world = new World(*_b2World, sf::Vector2f(6400, 100));
	for (int i = 0; i < _world->GetLandList().size(); i++)
		_objectManager->AddObject(_world->GetLandList()[i]);

	//Create the character and add it's objects to the game;
	_character = new Character(*_b2World, "Resources/blank/blank.json", "Resources/blank/blank.atlas");
	_objectManager->AddObject(_character);
	_objectManager->AddObject(_character->GetWeapon());
	_objectManager->AddObject(new WorldObject(*_b2World, sf::Vector2f(50, 50), sf::Vector2f(500, 0)));

	_player = new Player(*_character, sf::Vector2f(WINDOWSIZEX, WINDOWSIZEY));
	
	return passInit;
}

// Pocessing inputs from keyboard, mouse, joystick etc.
void Engine::ProcessInput()
{
	sf::Event evt;

	while (_window->pollEvent(evt))
	{
		if (evt.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			_window->close();
	}

	_player->ProcessInputs(*_window);
}

// Updates the game
void Engine::Update()
{
	_b2World->Step(WORLDTIME, 8, 3);

	_player->Update(*_window);
	_objectManager->Update(_deltaClock->getElapsedTime().asSeconds());
}

// Rendering the game to the screen
void Engine::RenderFrame()
{
	_window->clear(sf::Color::Black);

	_objectManager->Draw(*_window);

	_b2World->DrawDebugData();

	_window->display();
}

// Constructors and Deconstructors
Engine::Engine()
{
}

Engine::~Engine()
{
}
