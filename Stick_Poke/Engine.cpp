#include "Engine.h"

void Engine::MainLoop()
{
	while(window->isOpen())
	{
		ProcessInput();

		Update();

		RenderFrame();
	}
}

void Engine::Go()
{
	if(!Init())
		throw "Could not initialise Engine";

	MainLoop();
}

// Initialization of the ENGINE
bool Engine::Init()
{
	bool passInit = true;

	window = new sf::RenderWindow(sf::VideoMode(1024, 768), "Stick Poke"/*, sf::Style::Fullscreen*/);
	window->setMouseCursorVisible(true);
	window->setVerticalSyncEnabled(true);

	if(!window)
		passInit = false;

	return passInit;
}

// Pocessing inputs from keyboard, mouse, joystick etc.
void Engine::ProcessInput()
{
	sf::Event evt;

	while (window->pollEvent(evt))
	{
		if (evt.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window->close();
	}
}

// Updates the game
void Engine::Update()
{
}

// Rendering the game to the screen
void Engine::RenderFrame()
{
	window->clear(sf::Color::Black);
	window->display();
}

// Constructors and Deconstructors
Engine::Engine()
{
}

Engine::~Engine()
{
}
