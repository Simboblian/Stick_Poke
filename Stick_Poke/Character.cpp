#include "Character.h"

sf::Vector2f Character::CalculateElbow(sf::Vector2f Shoulder, sf::Vector2f Wrist)
{
	Shoulder = Shoulder - m_Position;
	Wrist = Wrist - m_Position;

	float ArmSectionLength = ARMSECTIONLENGTH;
	sf::Vector2f midSection = sf::Vector2f((Wrist.x + Shoulder.x) / 2, (Wrist.y + Shoulder.y) / 2);

	float midLength = Utility::GetMagnitude(midSection - Shoulder);

	float elbowDistance = sqrt(fabs((ArmSectionLength * ArmSectionLength) - (midLength * midLength)));
	sf::Vector2f elbow = Utility::Normalise(Wrist - Shoulder);

	elbow *= elbowDistance;

	sf::Vector2f elbowPos;

	elbowPos.x = -elbow.y;
	elbowPos.y = elbow.x;


	elbowPos += midSection;

	return elbowPos + m_Position;
}

void Character::UpdateArmPositions()
{
	m_BackShoulder = sf::Vector2f(m_Rect.getPosition().x - (m_Rect.getSize().x / 2), m_Rect.getPosition().y - (m_Rect.getSize().y / 2) + (m_Rect.getSize().y / 5));
	m_FrontShoulder = sf::Vector2f(m_Rect.getPosition().x + (m_Rect.getSize().x / 2), m_Rect.getPosition().y - (m_Rect.getSize().y / 2) + (m_Rect.getSize().y / 5));
	m_BackElbow = CalculateElbow(m_BackShoulder, m_Weapon->GetBackHandPos());
	m_FrontElbow = CalculateElbow(m_FrontShoulder, m_Weapon->GetFrontHandPos());

	sf::Vector2f bBicepPos = sf::Vector2f((m_BackShoulder.x + m_BackElbow.x) / 2, (m_BackShoulder.y + m_BackElbow.y) / 2);
	m_BackBicep.setPosition(bBicepPos);

	float bb = atan((m_BackElbow.y - m_BackShoulder.y) / (m_BackElbow.x - m_BackShoulder.x));
	m_BackBicep.setRotation((bb * 180 / ut::PI) + 90);

	m_BackElbowCircle.setPosition(m_BackElbow);

	sf::Vector2f bForearmPos = sf::Vector2f((m_BackElbow.x + m_Weapon->GetBackHandPos().x) / 2, (m_BackElbow.y + m_Weapon->GetBackHandPos().y) / 2);
	m_BackForearm.setPosition(bForearmPos);

	float bf = atan((m_Weapon->GetBackHandPos().y - m_BackElbow.y) / (m_Weapon->GetBackHandPos().x - m_BackElbow.x));
	m_BackForearm.setRotation((bf * 180 / ut::PI) + 90);

	sf::Vector2f fBicepPos = sf::Vector2f((m_FrontShoulder.x + m_FrontElbow.x) / 2, (m_FrontShoulder.y + m_FrontElbow.y) / 2);
	m_FrontBicep.setPosition(fBicepPos);

	float fb = atan((m_FrontElbow.y - m_FrontShoulder.y) / (m_FrontElbow.x - m_FrontShoulder.x));
	m_FrontBicep.setRotation((fb * 180 / ut::PI) + 90);

	m_FrontElbowCircle.setPosition(m_FrontElbow);

	sf::Vector2f fForearmPos = sf::Vector2f((m_FrontElbow.x + m_Weapon->GetFrontHandPos().x) / 2, (m_FrontElbow.y + m_Weapon->GetFrontHandPos().y) / 2);
	m_FrontForearm.setPosition(fForearmPos);

	float ff = atan((m_Weapon->GetFrontHandPos().y - m_FrontElbow.y) / (m_Weapon->GetFrontHandPos().x - m_FrontElbow.x));
	m_FrontForearm.setRotation((ff * 180 / ut::PI) + 90);
}

void Character::Draw(sf::RenderWindow &Window)
{
	Window.draw(m_FrontForearm);
	Window.draw(m_FrontElbowCircle);
	Window.draw(m_FrontBicep);
	Window.draw(m_Rect);
	Window.draw(m_BackBicep);
	Window.draw(m_BackElbowCircle);
	Window.draw(m_BackForearm);
	m_Weapon->Draw(Window, true);
}

void Character::Update(sf::Vector2f Gravity)
{
	b2Vec2 worldCenter = m_Body->GetWorldCenter();
	m_Velocity += Utility::B2VECtoSFVEC(m_Body->GetLinearVelocity(), true);

	m_Position = sf::Vector2f(Utility::B2VECtoSFVEC(m_Body->GetPosition(), true));

	m_Body->SetLinearVelocity(Utility::SFVECtoB2VEC(m_Velocity, true));

	UpdateArmPositions();

	m_Weapon->Update(m_WeaponPos, m_Position, false, false);
}

void Character::ReceiveInputs(ControlState State)
{
	m_WeaponPos = State.rStick;
	if (State.right)
		m_Velocity.x = 1.0f;
	else if (State.left)
		m_Velocity.x = -1.0f;
	else
		m_Velocity.x = 0;
}

Character::Character(b2World &World)
{
	m_GravityScale = 1;

	m_Rect.setSize(sf::Vector2f(50.0f, 100.0f));
	m_Rect.setOrigin(m_Rect.getSize().x / 2, m_Rect.getSize().y / 2);
	m_Rect.setPosition(0, 0);
	m_Rect.setFillColor(sf::Color::Yellow);

	m_BackBicep.setSize(sf::Vector2f(10.0f, ARMSECTIONLENGTH));
	m_BackBicep.setOrigin(m_BackBicep.getSize().x / 2, m_BackBicep.getSize().y / 2);
	m_BackBicep.setPosition(0, 0);
	m_BackBicep.setFillColor(sf::Color::Magenta);

	m_BackForearm.setSize(sf::Vector2f(10.0f, ARMSECTIONLENGTH));
	m_BackForearm.setOrigin(m_BackForearm.getSize().x / 2, m_BackForearm.getSize().y / 2);
	m_BackForearm.setPosition(0, 0);
	m_BackForearm.setFillColor(sf::Color::Magenta);

	m_FrontBicep.setSize(sf::Vector2f(10.0f, ARMSECTIONLENGTH));
	m_FrontBicep.setOrigin(m_FrontBicep.getSize().x / 2, m_FrontBicep.getSize().y / 2);
	m_FrontBicep.setPosition(0, 0);
	m_FrontBicep.setFillColor(sf::Color::Cyan);

	m_FrontForearm.setSize(sf::Vector2f(10.0f, ARMSECTIONLENGTH));
	m_FrontForearm.setOrigin(m_FrontForearm.getSize().x / 2, m_FrontForearm.getSize().y / 2);
	m_FrontForearm.setPosition(0, 0);
	m_FrontForearm.setFillColor(sf::Color::Cyan);

	m_BackElbowCircle.setRadius(5);
	m_BackElbowCircle.setOrigin(5, 5);
	m_BackElbowCircle.setFillColor(sf::Color::Magenta);
	m_BackElbowCircle.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_BackElbowCircle.setPosition(0, 0);

	m_FrontElbowCircle.setRadius(5);
	m_FrontElbowCircle.setOrigin(5, 5);
	m_FrontElbowCircle.setFillColor(sf::Color::Cyan);
	m_FrontElbowCircle.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_FrontElbowCircle.setPosition(0, 0);

	m_Weapon = new Weapon();
	m_Weapon->SetAnchorOffset(sf::Vector2f(-75.0, 15.0f));
	m_Weapon->SetControlRadius(50.0f);
	m_Weapon->SetControlOffset(sf::Vector2f(75.0f, 0.0f));
	m_Weapon->SetWeaponSize(sf::Vector2f(180.0, 10.0f));
	m_Weapon->SetWeaponOrigin(sf::Vector2f(160.0, 5.0f));
	m_Weapon->SetHitboxOffset(sf::Vector2f(15.0, 0.0f));
	m_Weapon->SetHitboxRadius(7.5f);

	for (int i = 0; i < m_BackArm.getVertexCount(); i++)
	{
		m_BackArm[i].color = sf::Color::Magenta;
	}

	for (int i = 0; i < m_BackArm.getVertexCount(); i++)
	{
		m_FrontArm[i].color = sf::Color::Cyan;
	}

	m_WeaponPos = sf::Vector2f(0, 0);

	CreateRoundedBody(World, m_Rect.getSize());

	m_State = IDLE;
}

Character::Character()
{
}

Character::~Character()
{
}
