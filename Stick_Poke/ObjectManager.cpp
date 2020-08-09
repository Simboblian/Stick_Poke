#include "ObjectManager.h"

void ObjectManager::Update(float Delta)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->Update(Delta);
	}
}

void ObjectManager::Draw(sf::RenderWindow & Window)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->Draw(Window);
	}
}

void ObjectManager::PopulateDead(std::vector<GameObject*>& Vector)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		if (_objects[i] /*is killed*/)
		{
			Vector.push_back(_objects[i]);
			delete _objects[i];
			_objects.erase(_objects.begin() + i);

			if (_objects.size() == 0)
				break;
		}
	}
}

void ObjectManager::KillDying(std::vector<GameObject*>& Vector)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		if (_objects[i] /*is dying*/)
		{
			Vector.push_back(_objects[i]);
			delete _objects[i];
			_objects.erase(_objects.begin() + i);

			if (_objects.size() == 0)
				break;
		}
	}
}

void ObjectManager::KillAll(std::vector<GameObject*>& Vector)
{
	int j = _objects.size();
	for (int i = 0; i < j; i++)
	{
		delete _objects[0];
		_objects.erase(_objects.begin() );

		if (_objects.size() == 0)
			break;
	}
}

ObjectManager::ObjectManager()
{
	_objects.clear();
}


ObjectManager::~ObjectManager()
{
}
