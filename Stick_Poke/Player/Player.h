#ifndef PLAYER_H
#define PLAYER_H
#include "Objects\Character.h"
#include "Player\Input.h"

class Player
{
private:
	Character *m_Character;
	Input *m_Input;

public:
	void Initialize();
	void Update();
	void ProcessInputs();

	Player();
	~Player();
};

#endif