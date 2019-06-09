#include "CollisionHandler.h"

void CollisionHandler::BeginContact(b2Contact * contact)
{
	std::pair<std::pair<GameObject*, b2Fixture*>, std::pair<GameObject*, b2Fixture*>> collision;

	for (int i = 0; i < m_ObjectManager.GetObjects().size(); i++)
	{
		for (b2Fixture* f = m_ObjectManager.GetObjects()[i]->GetBody()->GetFixtureList(); f; f = f->GetNext())
		{
			if (contact->GetFixtureA() == f)
				collision.first = std::pair<GameObject*, b2Fixture*>(m_ObjectManager.GetObjects()[i], f);
			if (contact->GetFixtureB() == f)
				collision.second = std::pair<GameObject*, b2Fixture*>(m_ObjectManager.GetObjects()[i], f);
		}
	}


	for (int i = 0; i < m_CollisionList.size(); i++)
	{
		if (m_CollisionList[i] == collision)
		{
			return;
		}
		else if (m_CollisionList[i] == std::pair<std::pair<GameObject*, b2Fixture*>, std::pair<GameObject*, b2Fixture*>>
			(std::pair<GameObject*, b2Fixture*>(collision.second.first, collision.second.second),
				std::pair<GameObject*, b2Fixture*>(collision.first.first, collision.first.second)))
		{
			return;
		}
	}

	m_CollisionList.push_back(collision);

	for (int i = 0; i < m_CollisionList.size(); i++)
	{
		if (m_CollisionList[i].first.first == m_ObjectManager.GetObjects()[1])
		{
			if (m_CollisionList[i].first.second->IsSensor())
			{
				m_ObjectManager.GetObjects()[1]->SetState(STANDING);
				continue;
			}
		}

		if (m_CollisionList[i].second.first == m_ObjectManager.GetObjects()[1])
		{
			if (m_CollisionList[i].second.second->IsSensor())
			{
				m_ObjectManager.GetObjects()[1]->SetState(STANDING);
				continue;
			}
		}
	}
}

void CollisionHandler::EndContact(b2Contact * contact)
{
	std::pair<std::pair<GameObject*, b2Fixture*>, std::pair<GameObject*, b2Fixture*>> collision;

	for (int i = 0; i < m_ObjectManager.GetObjects().size(); i++)
	{
		for (b2Fixture* f = m_ObjectManager.GetObjects()[i]->GetBody()->GetFixtureList(); f; f = f->GetNext())
		{
			if (contact->GetFixtureA() == f)
				collision.first = std::pair<GameObject*, b2Fixture*>(m_ObjectManager.GetObjects()[i], f);
			if (contact->GetFixtureB() == f)
				collision.second = std::pair<GameObject*, b2Fixture*>(m_ObjectManager.GetObjects()[i], f);
		}
	}

	for (int i = 0; i < m_CollisionList.size(); i++)
	{
		if (m_CollisionList[i] == collision)
		{
			if (m_CollisionList[i].first.first == m_ObjectManager.GetObjects()[1])
			{
				if (m_CollisionList[i].first.second->IsSensor())
				{
					m_ObjectManager.GetObjects()[1]->SetState(AIRBORNE);
					continue;
				}
			}

			if (m_CollisionList[i].second.first == m_ObjectManager.GetObjects()[1])
			{
				if (m_CollisionList[i].second.second->IsSensor())
				{
					m_ObjectManager.GetObjects()[1]->SetState(AIRBORNE);
					continue;
				}
			}
			m_CollisionList.erase(m_CollisionList.begin() + i);
			continue;
		}
		else if (m_CollisionList[i] == std::pair<std::pair<GameObject*, b2Fixture*>, std::pair<GameObject*, b2Fixture*>>
			(std::pair<GameObject*, b2Fixture*>(collision.second.first, collision.second.second),
				std::pair<GameObject*, b2Fixture*>(collision.first.first, collision.first.second)))
		{
			if (m_CollisionList[i].first.first == m_ObjectManager.GetObjects()[1])
			{
				if (m_CollisionList[i].first.second->IsSensor())
				{
					m_ObjectManager.GetObjects()[1]->SetState(AIRBORNE);
					continue;
				}
			}

			if (m_CollisionList[i].second.first == m_ObjectManager.GetObjects()[1])
			{
				if (m_CollisionList[i].second.second->IsSensor())
				{
					m_ObjectManager.GetObjects()[1]->SetState(AIRBORNE);
					continue;
				}
			}

			m_CollisionList.erase(m_CollisionList.begin() + i);
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

CollisionHandler::CollisionHandler(ObjectManager &ObjectManagerRef) : m_ObjectManager(ObjectManagerRef)
{
	m_CollisionList = std::vector<std::pair<std::pair<GameObject*, b2Fixture*>, std::pair<GameObject*, b2Fixture*>>>();
}

CollisionHandler::CollisionHandler() : m_ObjectManager(*new ObjectManager)
{
	m_CollisionList = std::vector<std::pair<std::pair<GameObject*, b2Fixture*>, std::pair<GameObject*, b2Fixture*>>>();
}

CollisionHandler::~CollisionHandler()
{
}