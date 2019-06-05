#ifndef _COLLISIONHANDLER_H
#define _COLLISIONHANDLER_H

#include <Box2D/Box2D.h>
#include "utility.h"

static class CollisionHandler : public b2ContactListener
{
private:
	//std::map<GameObject, GameObject> collidingObjects;
public:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

	CollisionHandler();
	~CollisionHandler();
};

#endif