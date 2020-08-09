#include "Character.h"

sf::Vector2f Character::CalculateElbow(sf::Vector2f Shoulder, sf::Vector2f Wrist)
{
	Shoulder = Shoulder - _position;
	Wrist = Wrist - _position;

	float ArmSectionLength = ARMSECTIONLENGTH;
	sf::Vector2f midSection = sf::Vector2f((Wrist.x + Shoulder.x) / 2, (Wrist.y + Shoulder.y) / 2);

	float midLength = Utility::GetMagnitude(midSection - Shoulder);

	float elbowDistance = sqrt(fabs((ArmSectionLength * ArmSectionLength) - (midLength * midLength)));
	sf::Vector2f elbow = Utility::Normalise(Wrist - Shoulder);

	elbow *= elbowDistance;

	sf::Vector2f elbowPos;

	if (_flip)
	{
		elbowPos.x = elbow.y;
		elbowPos.y = -elbow.x;
	}
	else
	{
		elbowPos.x = -elbow.y;
		elbowPos.y = elbow.x;
	}

	elbowPos += midSection;

	return elbowPos + _position;
}

void Character::UpdateArmPositions()
{
	int elbowDirection = 0;

	_flip ? elbowDirection = -90 : elbowDirection = 90;

	_backShoulder = sf::Vector2f(_rect.getPosition().x - (_rect.getSize().x / 2), _rect.getPosition().y - (_rect.getSize().y / 2) + (_rect.getSize().y / 5));
	_frontShoulder = sf::Vector2f(_rect.getPosition().x + (_rect.getSize().x / 2), _rect.getPosition().y - (_rect.getSize().y / 2) + (_rect.getSize().y / 5));
	_backElbow = CalculateElbow(_backShoulder, _weapon->GetBackHandPos());
	_frontElbow = CalculateElbow(_frontShoulder, _weapon->GetFrontHandPos());

	_backBicep.setPosition(Utility::MidPointOfTwoVectors(_backShoulder, _backElbow));
	_backBicep.setRotation((Utility::AngleBetweenTwoVectors(_backShoulder, _backElbow) * 180 / ut::PI) + elbowDirection);

	_backElbowCircle.setPosition(_backElbow);

	_backForearm.setPosition(Utility::MidPointOfTwoVectors(_backElbow, _weapon->GetBackHandPos()));
	_backForearm.setRotation((Utility::AngleBetweenTwoVectors(_backElbow, _weapon->GetBackHandPos()) * 180 / ut::PI) + elbowDirection);

	_frontBicep.setPosition(Utility::MidPointOfTwoVectors(_frontShoulder, _frontElbow));
	_frontBicep.setRotation((Utility::AngleBetweenTwoVectors(_frontElbow, _frontShoulder) * 180 / ut::PI) + elbowDirection);

	_frontElbowCircle.setPosition(_frontElbow);

	_frontForearm.setPosition(Utility::MidPointOfTwoVectors(_frontElbow, _weapon->GetFrontHandPos()));
	_frontForearm.setRotation((Utility::AngleBetweenTwoVectors(_frontElbow, _weapon->GetFrontHandPos()) * 180 / ut::PI) + elbowDirection);
}

void Character::Draw(sf::RenderWindow &Window)
{
	switch (_weapon->GetGrip())
	{
	default:
	case G_TWOHAND:
		if (_flip)
		{
			Window.draw(_backForearm);
			Window.draw(_backElbowCircle);
			Window.draw(_backBicep);
			Window.draw(_rect);
			Window.draw(_frontBicep);
			Window.draw(_frontElbowCircle);
			Window.draw(_frontForearm);
		}
		else
		{
			Window.draw(_frontForearm);
			Window.draw(_frontElbowCircle);
			Window.draw(_frontBicep);
			Window.draw(_rect);
			Window.draw(_backBicep);
			Window.draw(_backElbowCircle);
			Window.draw(_backForearm);
		}
		_weapon->Draw(Window, true);
		break;
	case G_FRONTHAND:
		_weapon->Draw(Window, true);
		if (_flip)
		{
			Window.draw(_backForearm);
			Window.draw(_backElbowCircle);
			Window.draw(_backBicep);
			Window.draw(_rect);
		}
		else
		{
			Window.draw(_frontForearm);
			Window.draw(_frontElbowCircle);
			Window.draw(_frontBicep);
			Window.draw(_rect);
		}
		break;
	case G_BACKHAND:
		if (_flip)
		{
			Window.draw(_backForearm);
			Window.draw(_backElbowCircle);
			Window.draw(_backBicep);
			Window.draw(_rect);
		}
		else
		{
			Window.draw(_frontForearm);
			Window.draw(_frontElbowCircle);
			Window.draw(_frontBicep);
			Window.draw(_rect);
		}
		_weapon->Draw(Window, true);
		break;
	}
	_life.Draw(Window);
	_energy.Draw(Window);
	_animation->Draw(&Window);
}

void Character::Update(float Delta)
{
	b2Vec2 worldCenter = _body->GetWorldCenter();

	if (Utility::GetMagnitude(_oldWeaponPos - _weaponPos) > 10)
		_energy.SetCurrent(_energy.GetCurrent() - 1);
	else
		_energy.StartRegen();

	if (_energy.IsEmpty())
	{
		_weapon->SetSpeed(2);
		_energy.SetColour(sf::Color::Red);
	}

	if (_energy.IsFull())
	{
		_weapon->ResetSpeed();
		_energy.SetColour(sf::Color::Yellow);
	}


	switch (_actionState)
	{
	default:
	case AS_STANCE0:

		if (_activeWeapon == 0)
		{
			_weapon->SetTargetOffset(sf::Vector2f(110.0f, 0.0f));
			_weapon->SetControlRadius(60);
			_weapon->SetAnchorOffset(sf::Vector2f(-75.0, 15.0f));
		}
		else
		{
			_weapon->SetAnchorOffset(sf::Vector2f(0.0, 25.0f));
			_weapon->SetTargetOffset(sf::Vector2f(40.0f, 10.0f));
			_weapon->SetControlRadius(40);
		}

		//Spear
		//
		break;
	case AS_STANCE1:
		if (_activeWeapon == 0)
		{
			_weapon->SetTargetOffset(sf::Vector2f(90.0f, 30.0f));
			_weapon->SetControlRadius(60);
			_weapon->SetAnchorOffset(sf::Vector2f(-75.0, 15.0f));
		}
		else
		{
			_weapon->SetAnchorOffset(sf::Vector2f(0.0, -15.0f));
			_weapon->SetTargetOffset(sf::Vector2f(100.0f, -15.0f));
			_weapon->SetControlRadius(10);
		}
		break;
	case AS_STANCE2:
		if (_activeWeapon == 0)
		{
			_weapon->SetTargetOffset(sf::Vector2f(90.0f, -30.0f));
			_weapon->SetControlRadius(60);
			_weapon->SetAnchorOffset(sf::Vector2f(-75.0, 15.0f));
		}
		else
		{
			_weapon->SetAnchorOffset(sf::Vector2f(0.0, 25.0f));
			_weapon->SetTargetOffset(sf::Vector2f(20.0f, 0.0f));
			_weapon->SetControlRadius(60);
		}
		break;
	}


	//------ MOVEMENT ------//
	_velocity = Utility::B2VECtoSFVEC(_body->GetLinearVelocity(), true);
	float xForce = 0;
	float yForce = 0;
	bool Impulse = false;

	switch (_moveState)
	{
	case MS_IDLE:
		if(_state == STANDING)
			xForce = _velocity.x * -2;
		break;
	case MS_WALKLEFT:
		if (_velocity.x > -100)
			xForce = -100;
		else if(_velocity.x < -100 && _state == STANDING)
			xForce = _velocity.x * -2;
		break;
	case MS_WALKRIGHT:
		if (_velocity.x < 100)
			xForce = 100;
		else if (_velocity.x > 100 && _state == STANDING)
			xForce = _velocity.x * -2;
		break;
	case MS_DASHLEFT:
		xForce = -200;
		Impulse = true;
		break;
	case MS_DASHRIGHT:
		xForce = 200;
		Impulse = true;
		break;
	case MS_JUMPLEFT:
		yForce = -200;
		xForce = -100;
		Impulse = true;
		break;
	case MS_JUMPRIGHT:
		yForce = -200;
		xForce = 100;
		Impulse = true;
		break;
	case MS_JUMPUP:
		yForce = -200;
		Impulse = true;
		break;
	}

	if(Impulse)
		_body->ApplyLinearImpulse(Utility::SFVECtoB2VEC(sf::Vector2f(xForce, yForce)), worldCenter, true);
	else
		_body->ApplyForce(Utility::SFVECtoB2VEC(sf::Vector2f(xForce, yForce)), worldCenter, true);

	//------ POSITIONS ------//
	_position = sf::Vector2f(Utility::B2VECtoSFVEC(_body->GetPosition(), true));
	_rect.setPosition(_position);
	_animation->SetPosition((sf::Vector2i)_position);

	_animation->Update(Delta);
	_weapon->Update(_weaponPos, _position, _rect.getSize(), _flip, false);
	_energy.Update(sf::Vector2f(_position.x, _position.y - _rect.getSize().y));
	_life.Update(sf::Vector2f(_position.x, _position.y - 3 - _rect.getSize().y - _rect.getSize().y / 20));

	UpdateArmPositions();
}

void Character::ReceiveInputs(Input* State)
{
	_oldWeaponPos = _weaponPos;

	_weaponPos = State->GetInputBuffer()->rStick;

	if (State->GetInputBuffer()->lStick.x < -20 || State->GetInputBuffer()->left)
	{
		if (!State->WasInputPressedAtFrame(Input::c_Movement, 1))
			_moveState = MS_WALKLEFT;
		else
			if (_state == STANDING)
				_moveState = MS_DASHLEFT;

		if((State->GetInputBuffer()->lStick.y < -20 || State->GetInputBuffer()->up)&& State->WasInputPressedAtFrame(Input::c_Movement, 1))
			if(_state != AIRBORNE)
				_moveState = MS_JUMPLEFT;
	}
	else if (State->GetInputBuffer()->lStick.x > 20 || State->GetInputBuffer()->right)
	{
		if (!State->WasInputPressedAtFrame(Input::c_Movement, 1))
			_moveState = MS_WALKRIGHT;
		else
			if(_state == STANDING)
				_moveState = MS_DASHRIGHT;

		if ((State->GetInputBuffer()->lStick.y < -20 || State->GetInputBuffer()->up) && State->WasInputPressedAtFrame(Input::c_Movement, 1))
			if (_state != AIRBORNE)
				_moveState = MS_JUMPRIGHT;
	}
	else
	{
		_moveState = MS_IDLE;

		if ((State->GetInputBuffer()->lStick.y < -20 || State->GetInputBuffer()->up) && State->WasInputPressedAtFrame(Input::c_Movement, 1))
			if (_state != AIRBORNE)
				_moveState = MS_JUMPUP;
	}

	if (State->GetInputBuffer()->stance1)
	{
		_actionState = AS_STANCE1;
	}
	else if (State->GetInputBuffer()->stance2)
	{
		_actionState = AS_STANCE2;
	}
	else
	{
		_actionState = AS_STANCE0;
	}

	if (State->GetInputBuffer()->item1)
	{
		_activeWeapon = 0;
		_weapon->SetAnchorOffset(sf::Vector2f(-75.0, 15.0f));
		_weapon->SetControlRadius(60.0f);
		_weapon->SetTargetOffset(sf::Vector2f(110.0f, 0.0f));
		_weapon->SetWeaponSize(sf::Vector2f(180.0, 10.0f));
		_weapon->SetWeaponOrigin(sf::Vector2f(160.0, 5.0f));
		_weapon->SetHitboxOffset(sf::Vector2f(15.0, 0.0f));
		_weapon->SetFrontHandOffset(75);
		_weapon->SetBackHandOffset(140);
		_weapon->SetHitboxRadius(7.5f);
		_weapon->SetTopSpeed(20);
		_weapon->SetGrip(G_TWOHAND);
	}

	if (State->GetInputBuffer()->item2)
	{
		_activeWeapon = 1;
		_weapon->SetAnchorOffset(sf::Vector2f(0.0, 25.0f));
		_weapon->SetControlRadius(40.0f);
		_weapon->SetTargetOffset(sf::Vector2f(40.0f, 10.0f));
		_weapon->SetWeaponSize(sf::Vector2f(75.0, 10.0f));
		_weapon->SetWeaponOrigin(sf::Vector2f(15.0, 5.0f));
		_weapon->SetHitboxOffset(sf::Vector2f(50.0, 0.0f));
		_weapon->SetHitboxRadius(7.5f);
		_weapon->SetFrontHandOffset(5);
		_weapon->SetTopSpeed(20);
		_weapon->SetGrip(G_FRONTHAND);
	}
}

Character::Character(b2World &World, const char* JsonFilepath, const char* AtlasFilepath)
{
	_animation = new AnimationHandler(JsonFilepath, AtlasFilepath, sf::Vector2i(0, 0));
	_rect.setSize(sf::Vector2f(50.0f, 100.0f));
	_rect.setOrigin(_rect.getSize().x / 2, _rect.getSize().y / 2);
	_rect.setPosition(0, 0);
	_rect.setFillColor(sf::Color::Yellow);

	_backBicep.setSize(sf::Vector2f(10.0f, ARMSECTIONLENGTH));
	_backBicep.setOrigin(_backBicep.getSize().x / 2, _backBicep.getSize().y / 2);
	_backBicep.setPosition(0, 0);
	_backBicep.setFillColor(sf::Color::Magenta);

	_backForearm.setSize(sf::Vector2f(10.0f, ARMSECTIONLENGTH));
	_backForearm.setOrigin(_backForearm.getSize().x / 2, _backForearm.getSize().y / 2);
	_backForearm.setPosition(0, 0);
	_backForearm.setFillColor(sf::Color::Magenta);

	_frontBicep.setSize(sf::Vector2f(10.0f, ARMSECTIONLENGTH));
	_frontBicep.setOrigin(_frontBicep.getSize().x / 2, _frontBicep.getSize().y / 2);
	_frontBicep.setPosition(0, 0);
	_frontBicep.setFillColor(sf::Color::Cyan);

	_frontForearm.setSize(sf::Vector2f(10.0f, ARMSECTIONLENGTH));
	_frontForearm.setOrigin(_frontForearm.getSize().x / 2, _frontForearm.getSize().y / 2);
	_frontForearm.setPosition(0, 0);
	_frontForearm.setFillColor(sf::Color::Cyan);

	_backElbowCircle.setRadius(5);
	_backElbowCircle.setOrigin(5, 5);
	_backElbowCircle.setFillColor(sf::Color::Magenta);
	_backElbowCircle.setOutlineColor(sf::Color(0, 0, 0, 0));
	_backElbowCircle.setPosition(0, 0);

	_frontElbowCircle.setRadius(5);
	_frontElbowCircle.setOrigin(5, 5);
	_frontElbowCircle.setFillColor(sf::Color::Cyan);
	_frontElbowCircle.setOutlineColor(sf::Color(0, 0, 0, 0));
	_frontElbowCircle.setPosition(0, 0);

	_activeWeapon = 0;
	_weapon = new Weapon(World);
	_weapon->SetControlRadius(60.0f);
	_weapon->SetAnchorOffset(sf::Vector2f(-75.0, 15.0f));
	_weapon->SetTargetOffset(sf::Vector2f(110.0f, 0.0f));
	_weapon->SetWeaponSize(sf::Vector2f(180.0, 10.0f));
	_weapon->SetWeaponOrigin(sf::Vector2f(160.0, 5.0f));
	_weapon->SetHitboxOffset(sf::Vector2f(15.0, 0.0f));
	_weapon->SetFrontHandOffset(75);
	_weapon->SetBackHandOffset(140);
	_weapon->SetHitboxRadius(7.5f);
	_weapon->SetTopSpeed(20);
	_weapon->SetGrip(G_TWOHAND);

	for (int i = 0; i < _backArm.getVertexCount(); i++)
	{
		_backArm[i].color = sf::Color::Magenta;
	}

	for (int i = 0; i < _backArm.getVertexCount(); i++)
	{
		_frontArm[i].color = sf::Color::Cyan;
	}

	_energy = UIProgressBar(sf::Vector2f(_position.x, _position.y - _rect.getSize().y), sf::Vector2f(_rect.getSize().x, _rect.getSize().y / 20));
	_energy.SetColour(sf::Color::Yellow);
	_energy.SetMax(100);
	_energy.AllowRegen(60);

	_life = UIProgressBar(sf::Vector2f(_position.x, _position.y - _rect.getSize().y - _rect.getSize().y / 20), sf::Vector2f(_rect.getSize().x, _rect.getSize().y / 20));
	_life.SetMax(100);
	_life.SetColour(sf::Color::Green);

	_weaponPos = sf::Vector2f(0, 0);

	InitRoundedBody(World, _rect.getSize());

	_state = IDLE;

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(Utility::ScaleToB2(_rect.getSize().x / 2.5), Utility::ScaleToB2(_rect.getSize().y / 20), Utility::SFVECtoB2VEC(sf::Vector2f(0, _rect.getSize().y / 2), true), 0);
	b2FixtureDef myFixtureDef;
	myFixtureDef.isSensor = true;
	myFixtureDef.shape = &polygonShape;
	b2Fixture* footSensorFixture = _body->CreateFixture(&myFixtureDef);

	_body->SetUserData((void*)ut::b_Character);
	_body->SetFixedRotation(true);
	_body->GetFixtureList()->SetDensity(1);
	_body->GetFixtureList()->SetFriction(0);
	_body->GetFixtureList()->SetUserData((void*)ut::f_Hurtbox);
	_body->GetFixtureList()->GetNext()->SetUserData((void*)ut::f_Foot);
}

Character::Character()
{
}

Character::~Character()
{
}
