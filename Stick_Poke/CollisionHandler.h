#ifndef _COLLISIONHANDLER_H
#define _COLLISIONHANDLER_H

#include <Box2D/Box2D.h>
#include "ObjectManager.h"
#include "utility.h"

static class CollisionHandler : public b2ContactListener
{
private:
	ObjectManager &m_ObjectManager;
	std::vector<std::pair<std::pair<GameObject*, b2Fixture*>, std::pair<GameObject*, b2Fixture*>>> m_CollisionList;
public:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

	void Update();

	CollisionHandler(ObjectManager &ObjectManagerRef);

	CollisionHandler();
	~CollisionHandler();
};

#endif