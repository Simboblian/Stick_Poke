#ifndef _ANIMATIONHANDLER_H
#define _ANIMATIONHANDLER_H

#include <SFML\Graphics.hpp>
#include <spine\spine-sfml.h>

using namespace spine;
using namespace std;

#define REAL_DEALTA 0.016755

class AnimationHandler
{
private:
	Atlas *_atlas;
	SkeletonBounds *_bounds;
	SkeletonDrawable *_drawable;
	Slot *_headSlot;
	SkeletonJson *_json;
	Skeleton *_skeleton;
	SkeletonData *_skeletonData;
	AnimationStateData *_stateData;

	sf::Clock _deltaClock;

	string _animationName;
public:
	AnimationHandler();
	AnimationHandler(const char* filepath);

	void AddAnimation(string AnimationName, bool Flip, bool Loop);
	void Draw(sf::RenderWindow *Window);
	string GetName() { return AnimationState_getCurrent(_drawable->state, 0)->animation->name; };
	SkeletonBounds* GetBounds() { return _bounds; };
	SkeletonData* GetData() { return _skeletonData; };
	Skeleton* GetSkeleton() { return _skeleton; };
	void SetAnimation(string AnimationName, bool Flip, bool Loop);	
	void Update(sf::Vector2f Position, int frames = NULL, float delta = REAL_DEALTA);
	
	~AnimationHandler();
};

#endif