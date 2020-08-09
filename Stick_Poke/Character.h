#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "GameObject.h"
#include "UIProgressBar.h"
#include "AnimationHandler.h"
#include "Input.h"
#include "Weapon.h"

#define ARMSECTIONLENGTH 40

enum MoveState
{
	MS_IDLE,
	MS_WALKLEFT,
	MS_WALKRIGHT,
	MS_RUNLEFT,
	MS_RUNRIGHT,
	MS_DASHLEFT,
	MS_DASHRIGHT,
	MS_JUMPLEFT,
	MS_JUMPRIGHT,
	MS_JUMPUP
};

enum ActionState
{
	AS_STANCE0,
	AS_STANCE1,
	AS_STANCE2
};

class Character : public GameObject
{
private:
	AnimationHandler* _animation;

	bool _flip = false;

	MoveState _moveState = MS_IDLE;
	ActionState _actionState = AS_STANCE0;
	int _activeWeapon = 0;

	UIProgressBar _energy;
	UIProgressBar _life;

	sf::RectangleShape _rect;

	sf::RectangleShape _backBicep;
	sf::CircleShape _backElbowCircle;
	sf::RectangleShape _backForearm;

	sf::RectangleShape _frontBicep;
	sf::CircleShape _frontElbowCircle;
	sf::RectangleShape _frontForearm;

	sf::VertexArray _backArm;
	sf::VertexArray _frontArm;
	sf::Vector2f _velocity;
	sf::Vector2f _oldWeaponPos;
	sf::Vector2f _weaponPos;
	sf::Vector2f _backShoulder;
	sf::Vector2f _backElbow;
	sf::Vector2f _frontShoulder;
	sf::Vector2f _frontElbow;

	float deg = 90;

	Weapon* _weapon;
	Weapon* _weapon1;
	Weapon* _weapon2;
	sf::Vector2f CalculateElbow(sf::Vector2f Shoulder, sf::Vector2f Wrist);
	void UpdateArmPositions();
public:
	//spine::SkeletonDrawable* GetDrawable() { return m_Animation->GetDrawable(); };

	void Draw(sf::RenderWindow &Window);
	void Update(float Delta);

	void SetState(state State) { _state = State; };
	sf::RectangleShape GetShape() { return _rect; };
	sf::Vector2f GetWeaponOffset() { return _weapon->GetWeaponOffset(); };
	Weapon* GetWeapon() { return _weapon; };
	void ReceiveInputs(Input* State);

	Character(b2World& World, const char* JsonFilepath, const char* AtlasFilepath);
	Character();
	~Character();
};

#endif
