#include "CollisionHandler.h"

void CollisionHandler::BeginContact(b2Contact * contact)
{
	std::pair<std::pair<GameObject*, b2Fixture*>, std::pair<GameObject*, b2Fixture*>> collision;

	for (int i = 0; i < _objectManager.GetObjects().size(); i++)
	{
		for (b2Fixture* f = _objectManager.GetObjects()[i]->GetBody()->GetFixtureList(); f; f = f->GetNext())
		{
			if (contact->GetFixtureA() == f)
				collision.first = std::pair<GameObject*, b2Fixture*>(_objectManager.GetObjects()[i], f);
			if (contact->GetFixtureB() == f)
				collision.second = std::pair<GameObject*, b2Fixture*>(_objectManager.GetObjects()[i], f);
		}
	}

	for (int i = 0; i < _collisionList.size(); i++)
	{
		if (_collisionList[i] == collision)
		{
			return;
		}
		else if (_collisionList[i] == std::pair<std::pair<GameObject*, b2Fixture*>, std::pair<GameObject*, b2Fixture*>>
			(std::pair<GameObject*, b2Fixture*>(collision.second.first, collision.second.second),
				std::pair<GameObject*, b2Fixture*>(collision.first.first, collision.first.second)))
		{
			return;
		}
	}

	_collisionList.push_back(collision);
	
	if (_collisionList.back().first.second->GetBody()->GetUserData() == (void*)ut::b_Character)
	{
		if (_collisionList.back().first.second->GetUserData() == (void*)ut::f_Foot)
			if (_collisionList.back().second.second->GetUserData() == (void*)ut::f_Floor)
			{
				_collisionList.back().first.first->SetState(STANDING);
				return;
			}
	}
	else if (_collisionList.back().first.second->GetBody()->GetUserData() == (void*)ut::b_Weapon)
	{
		if (_collisionList.back().first.second->GetUserData() == (void*)ut::f_Hitbox)
			if (_collisionList.back().second.second->GetBody()->GetUserData() == (void*)ut::b_Doodad)
				if (_collisionList.back().second.second->GetUserData() == (void*)ut::f_Hurtbox)
				{
					_collisionList.back().second.second->GetBody()->ApplyLinearImpulse(Utility::SFVECtoB2VEC(_collisionList.back().first.first->GetHitVector(), true), _collisionList.back().second.second->GetBody()->GetWorldCenter(), true);
					return;
				}
	}

	if (_collisionList.back().second.second->GetBody()->GetUserData() == (void*)ut::b_Character)
	{
		if (_collisionList.back().second.second->GetUserData() == (void*)ut::f_Foot)
			if (_collisionList.back().first.second->GetUserData() == (void*)ut::f_Floor)
			{
				_collisionList.back().second.first->SetState(STANDING);
				return;
			}
	}
	else if (_collisionList.back().second.second->GetBody()->GetUserData() == (void*)ut::b_Weapon)
	{
		if (_collisionList.back().second.second->GetUserData() == (void*)ut::f_Hitbox)
			if (_collisionList.back().first.second->GetBody()->GetUserData() == (void*)ut::b_Doodad)
				if (_collisionList.back().first.second->GetUserData() == (void*)ut::f_Hurtbox)
				{
					_collisionList.back().first.second->GetBody()->ApplyLinearImpulse(Utility::SFVECtoB2VEC(_collisionList.back().second.first->GetHitVector(), true), _collisionList.back().first.second->GetBody()->GetWorldCenter(), true);
					return;
				}
	}
}

void CollisionHandler::EndContact(b2Contact * contact)
{
	std::pair<std::pair<GameObject*, b2Fixture*>, std::pair<GameObject*, b2Fixture*>> collision;

	for (int i = 0; i < _objectManager.GetObjects().size(); i++)
	{
		for (b2Fixture* f = _objectManager.GetObjects()[i]->GetBody()->GetFixtureList(); f; f = f->GetNext())
		{
			if (contact->GetFixtureA() == f)
				collision.first = std::pair<GameObject*, b2Fixture*>(_objectManager.GetObjects()[i], f);
			if (contact->GetFixtureB() == f)
				collision.second = std::pair<GameObject*, b2Fixture*>(_objectManager.GetObjects()[i], f);
		}
	}


	for (int i = 0; i < _collisionList.size(); i++)
	{
		if (_collisionList[i] == collision)
		{

			if (_collisionList[i].first.second->GetBody()->GetUserData() == (void*)ut::b_Character)
			{
				if (_collisionList[i].first.second->GetUserData() == (void*)ut::f_Foot)
					if (_collisionList[i].second.second->GetUserData() == (void*)ut::f_Floor)
					{
						_collisionList[i].first.first->SetState(AIRBORNE);
					}
			}

			if (_collisionList[i].second.second->GetBody()->GetUserData() == (void*)ut::b_Character)
			{
				if (_collisionList[i].second.second->GetUserData() == (void*)ut::f_Foot)
					if (_collisionList[i].first.second->GetUserData() == (void*)ut::f_Floor)
					{
						_collisionList[i].second.first->SetState(AIRBORNE);
					}
			}

			_collisionList.erase(_collisionList.begin() + i);
			continue;
		}
	}
}

void CollisionHandler::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
}

void CollisionHandler::PostSolve(b2Contact * contact, const b2ContactImpulse * impulse)
{
}

void CollisionHandler::Update()
{
}

CollisionHandler::CollisionHandler(ObjectManager &ObjectManagerRef) : _objectManager(ObjectManagerRef)
{
	_collisionList = std::vector<std::pair<std::pair<GameObject*, b2Fixture*>, std::pair<GameObject*, b2Fixture*>>>();
}

CollisionHandler::CollisionHandler() : _objectManager(*new ObjectManager)
{
	_collisionList = std::vector<std::pair<std::pair<GameObject*, b2Fixture*>, std::pair<GameObject*, b2Fixture*>>>();
}

CollisionHandler::~CollisionHandler()
{
}