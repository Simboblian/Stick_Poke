#ifndef _PLAYER_H
#define _PLAYER_H

#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Camera.h"
#include "Input.h"



class Player
{
private:
	Character defaultChar;
	Character &_character;

	Camera *_camera;
	Input *_input;

public:
	void Initialize();
	void Update(sf::RenderWindow &Window);
	void ProcessInputs(sf::RenderWindow &Window);

	Player(Character &Char, sf::Vector2f CameraSize);
	Player();
	~Player();
};

#endif