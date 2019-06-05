#include "Engine.h"

void Engine::Go()
{
	if (!Init())
		throw "Could not initialise Engine";

	MainLoop();
}

void Engine::MainLoop()
{
	while(m_Window->isOpen())
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

	m_Window = new sf::RenderWindow(sf::VideoMode(WINDOWSIZEX, WINDOWSIZEY), "Stick Poke"/*, sf::Style::Fullscreen*/);
	m_Window->setFramerateLimit(FPS_DEFAULT);
	//m_Window->setMouseCursorGrabbed(true);
	//m_Window->setMouseCursorVisible(false);

	if (!m_Window)
		passInit = false;


	m_B2World = new b2World(Utility::SFVECtoB2VEC(GRAVITY, false));

	m_DebugDraw = new SFMLDebugDraw(*m_Window);
	uint32 _flags = 0;
	//_flags += b2Draw::e_aabbBit;
	//_flags += b2Draw::e_centerOfMassBit;
	//_flags += b2Draw::e_pairBit;
	//_flags += b2Draw::e_jointBit;
	_flags += b2Draw::e_shapeBit;
	m_DebugDraw->SetFlags(_flags);

	m_B2World->SetDebugDraw(m_DebugDraw);

	m_CollisionHandler = new CollisionHandler;
	m_B2World->SetContactListener(m_CollisionHandler);

	m_ObjectManager = new ObjectManager();

	//Create the world and add it's objects to the game;
	m_World = new World(*m_B2World, sf::Vector2f(1600, 100));
	for (int i = 0; i < m_World->GetLandList().size(); i++)
		m_ObjectManager->AddObject(m_World->GetLandList()[i]);

	//Create the character and add it's objects to the game;
	m_Character = new Character(*m_B2World);
	m_ObjectManager->AddObject(m_Character);

	m_Player = new Player(*m_Character, sf::Vector2f(WINDOWSIZEX, WINDOWSIZEY));
	
	return passInit;
}

// Pocessing inputs from keyboard, mouse, joystick etc.
void Engine::ProcessInput()
{
	sf::Event evt;

	while (m_Window->pollEvent(evt))
	{
		if (evt.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			m_Window->close();
	}

	m_Player->ProcessInputs(*m_Window);
}

// Updates the game
void Engine::Update()
{
	m_B2World->Step(WORLDTIME, 8, 3);

	m_ObjectManager->Update(GRAVITY);
	m_Player->Update(*m_Window);
}

// Rendering the game to the screen
void Engine::RenderFrame()
{
	m_Window->clear(sf::Color::Black);

	m_ObjectManager->Draw(*m_Window);
	m_B2World->DrawDebugData();

	m_Window->display();
}

// Constructors and Deconstructors
Engine::Engine()
{
}

Engine::~Engine()
{
}
