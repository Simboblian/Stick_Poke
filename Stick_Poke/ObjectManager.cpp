#include "ObjectManager.h"

void ObjectManager::Update()
{
	for (int i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->Update();
	}
}

void ObjectManager::Draw(sf::RenderWindow & Window)
{
	for (int i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->Draw(Window);
	}
}

void ObjectManager::PopulateDead(std::vector<GameObject*>& Vector)
{
	for (int i = 0; i < m_Objects.size(); i++)
	{
		if (m_Objects[i] /*is killed*/)
		{
			Vector.push_back(m_Objects[i]);
			delete m_Objects[i];
			m_Objects.erase(m_Objects.begin() + i);

			if (m_Objects.size() == 0)
				break;
		}
	}
}

void ObjectManager::KillDying(std::vector<GameObject*>& Vector)
{
	for (int i = 0; i < m_Objects.size(); i++)
	{
		if (m_Objects[i] /*is dying*/)
		{
			Vector.push_back(m_Objects[i]);
			delete m_Objects[i];
			m_Objects.erase(m_Objects.begin() + i);

			if (m_Objects.size() == 0)
				break;
		}
	}
}

void ObjectManager::KillAll(std::vector<GameObject*>& Vector)
{
	int j = m_Objects.size();
	for (int i = 0; i < j; i++)
	{
		delete m_Objects[0];
		m_Objects.erase(m_Objects.begin() );

		if (m_Objects.size() == 0)
			break;
	}
}

ObjectManager::ObjectManager()
{
	m_Objects.clear();
}


ObjectManager::~ObjectManager()
{
}
