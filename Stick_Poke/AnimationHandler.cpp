#include "AnimationHandler.h"

void AnimationHandler::Update(sf::Vector2f Position, int frames, float delta)
{
	_skeleton->x = Position.x;
	_skeleton->y = Position.y;
	Skeleton_updateWorldTransform(_skeleton);

	SkeletonBounds_update(_bounds, _skeleton, true);

	if(frames != NULL)
	{
		float duration = AnimationState_getCurrent(_drawable->state, 0)->animation->duration;
		delta = (duration / frames);
	}
	
	_drawable->update(delta);
}

void AnimationHandler::SetAnimation(string AnimationName, bool Flip, bool Loop)
{
	const char* a = AnimationName.c_str();
	_skeleton->flipX = Flip;
	if(_animationName != AnimationName)
		AnimationState_setAnimationByName(_drawable->state, 0, a, Loop);
	
	_animationName = AnimationName;
}

void AnimationHandler::AddAnimation(string AnimationName, bool Flip, bool Loop)
{
	const char* a = AnimationName.c_str();
	_skeleton->flipX = Flip;
	if(_animationName != AnimationName)
		AnimationState_addAnimationByName(_drawable->state, 0, a, Loop, 0);
	
	_animationName = AnimationName;
}

void AnimationHandler::Draw(sf::RenderWindow *Window)
{
	Window->draw(*_drawable);
}

AnimationHandler::AnimationHandler()
{
}

AnimationHandler::AnimationHandler(const char* filepath)
{
	char result[100];
	strcpy(result, filepath);
	strcat(result, ".atlas");
	_atlas = Atlas_createFromFile(result, 0);
	_json = SkeletonJson_create(_atlas);
	_json->scale = 0.85f;
	strcpy(result, filepath);
	strcat(result, ".json");
	_skeletonData = SkeletonJson_readSkeletonDataFile(_json, result);
	if (!_skeletonData)
	{
		printf("%s\n", _json->error);
	}
	SkeletonJson_dispose(_json);
	_bounds = SkeletonBounds_create();

	_stateData = AnimationStateData_create(_skeletonData);

	_drawable = new SkeletonDrawable(_skeletonData, _stateData);
	_drawable->timeScale = 1;

	_skeleton = _drawable->skeleton;
	_skeleton->flipX = false;
	_skeleton->flipY = false;
	Skeleton_setToSetupPose(_skeleton);
}

AnimationHandler::~AnimationHandler()
{
}
