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

	m_Window = new RenderWindow(VideoMode(WINDOWSIZEX, WINDOWSIZEY), "Stick Poke"/*, sf::Style::Fullscreen*/);
	m_Window->setFramerateLimit(FPS_DEFAULT);

	if (!m_Window)
		passInit = false;

	m_Camera = new Camera(Vector2f(WINDOWSIZEX, WINDOWSIZEY));
	m_Camera->SetPosition(Vector2f(WINDOWSIZEX / 2, WINDOWSIZEY / 2));

	m_B2World = new b2World(b2Vec2(0.0f, GRAVITY));
	m_World = new World(*m_B2World, Vector2f(1600, 100));
	
	m_Character = new Character(*m_B2World);

	m_Player = new Player();

	m_DebugDraw = new SFMLDebugDraw(*m_Window);
	m_B2World->SetDebugDraw(m_DebugDraw);
	m_DebugDraw->SetFlags(b2Draw::e_shapeBit);
	m_DebugDraw->AppendFlags(b2Draw::e_jointBit);
	
	return passInit;
}

// Pocessing inputs from keyboard, mouse, joystick etc.
void Engine::ProcessInput()
{
	Event evt;

	while (m_Window->pollEvent(evt))
	{
		if (evt.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
			m_Window->close();
	}

	m_Player->ProcessInputs();
}

// Updates the game
void Engine::Update()
{
	m_B2World->Step(1 / FPS_DEFAULT, 160, 160);

	m_World->Update();
	m_Player->Update();
	m_Character->Update();
	m_Camera->SetPosition(m_World->GetCenter());
	m_Camera->Update(*m_Window);
}

// Rendering the game to the screen
void Engine::RenderFrame()
{
	m_Window->clear(Color::Black);
	m_World->Draw(*m_Window);
	m_Character->Draw(*m_Window);
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
