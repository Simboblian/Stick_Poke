#ifndef _WORLD_H
#define _WORLD_H

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include <vector>

#define SIZE 100
#define SCALE 32.0f

using namespace sf;
using namespace std;

class World
{
private:
	vector<RectangleShape*> m_RectList;
	Vector2f m_Position, m_Origin, m_Size;
	Color m_Color1 = Color::Magenta, m_Color2 = Color::Blue;
	b2Body* m_Body;

	b2Vec2 SFVECtoB2VEC(Vector2f vector, bool scale = false) { return b2Vec2(vector.x / (scale ? SCALE : 1.f), vector.y / (scale ? SCALE : 1.f)); };
	Vector2f B2VECtoSFVEC(b2Vec2 vector, bool scale = false) { return Vector2f(vector.x * (scale ? SCALE : 1.f), vector.y * (scale ? SCALE : 1.f)); };
public:
	void Update();
	void Draw(RenderWindow &Window);

	World(b2World &World, Vector2f Size);
	World();
	~World();
};

#endif // !_WORLD_H
