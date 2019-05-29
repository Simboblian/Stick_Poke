#ifndef _PLAYER_H
#define _PLAYER_H

#include "Character.h"
#include "Input.h"

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