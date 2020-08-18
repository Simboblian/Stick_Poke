#include "AnimationHandler.h"

void AnimationHandler::SetPosition(sf::Vector2i Position)
{
	_drawable->skeleton->setPosition(Position.x, Position.y);
}

void AnimationHandler::SetPosition(float x, float y)
{
	_drawable->skeleton->setPosition(x, y);
}

void AnimationHandler::SetAnimation(const char* Animation)
{
	_drawable->state->setAnimation(0, Animation, true);
}

void AnimationHandler::Update(float Delta, bool Flip)
{
	if (Flip != _flip)
	{
		_flip = Flip;

		if (_flip)
			_drawable->skeleton->setScaleX(-1);
		else
			_drawable->skeleton->setScaleX(1);

	}

	_drawable->update(Delta);
}

void AnimationHandler::Draw(sf::RenderWindow* Window)
{
	Window->draw(*_drawable);
}

AnimationHandler::AnimationHandler()
{
}

AnimationHandler::AnimationHandler(const char* jsonFilepath, const char* atlasFilepath, sf::Vector2i Position)
{
	spine::SFMLTextureLoader textureLoader;
	spine::Atlas* atlas = new spine::Atlas(atlasFilepath, &textureLoader);
	spine::SkeletonJson json = spine::SkeletonJson(atlas);
	spine::SkeletonData* skeleData = json.readSkeletonDataFile(jsonFilepath);

	spine::AnimationStateData* stateData = new spine::AnimationStateData(skeleData);
	stateData->setDefaultMix(1.0f);

	_drawable = new spine::SkeletonDrawable(skeleData, stateData);
	_drawable->timeScale = 2;
	_drawable->setUsePremultipliedAlpha(true);


	_skeleton = _drawable->skeleton;
	_skeleton->setToSetupPose();

	_skeleton->setPosition(Position.x, Position.y);
	_skeleton->updateWorldTransform();

	_drawable->state->addAnimation(0, "m_stand", true, 0);
}

AnimationHandler::~AnimationHandler()
{
}
