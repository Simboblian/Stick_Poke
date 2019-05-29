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

	if (!m_Window)
		passInit = false;

	m_Camera = new Camera(sf::Vector2f(WINDOWSIZEX, WINDOWSIZEY));
	m_Camera->SetPosition(sf::Vector2f(WINDOWSIZEX / 2, WINDOWSIZEY / 2));

	m_ObjectManager = new ObjectManager();

	//Create the world and add it's objects to the game;
	m_World = new World(sf::Vector2f(1600, 100));
	for (int i = 0; i < m_World->GetLandList().size(); i++)
		m_ObjectManager->AddObject(m_World->GetLandList()[i]);

	//Create the character and add it's objects to the game;
	m_Character = new Character();
	m_ObjectManager->AddObject(m_Character);

	m_Player = new Player();
	
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

	m_Player->ProcessInputs();
}

// Updates the game
void Engine::Update()
{
	m_Player->Update();
	m_ObjectManager->Update(GRAVITY);
	m_Camera->SetPosition(m_World->GetCenter());
	m_Camera->Update(*m_Window);
}

// Rendering the game to the screen
void Engine::RenderFrame()
{
	m_Window->clear(sf::Color::Black);
	m_ObjectManager->Draw(*m_Window);
	m_Window->display();
}

// Constructors and Deconstructors
Engine::Engine()
{
}

Engine::~Engine()
{
}
