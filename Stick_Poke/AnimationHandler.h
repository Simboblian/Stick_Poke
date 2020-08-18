#ifndef _ANIMATION_HANDLER_H
#define _ANIMATION_HANDLER_H

#include <spine\spine-sfml.h>
#include <SFML/Graphics.hpp>

#define REALDEALTA 0.016755

class AnimationHandler
{
private:	
	spine::SkeletonDrawable* _drawable;
	spine::Skeleton* _skeleton;

	bool _flip = false;
	std::string _animationName;
public:
	void Update(float Delta, bool Flip);
	void Draw(sf::RenderWindow* Window);

	spine::SkeletonDrawable* GetDrawable() { return _drawable; };
	sf::Vector2i GetPosition() { return sf::Vector2i(_skeleton->getX(), _skeleton->getY()); };

	sf::Vector2f GetBonePosition(const spine::String Bone) { return sf::Vector2f(_drawable->skeleton->findBone(Bone)->getWorldX(), _drawable->skeleton->findBone(Bone)->getWorldY()); };
	void ShowFrontArm(bool Show) { _drawable->skeleton->findBone("FF_Bone")->setActive(Show); _drawable->skeleton->findBone("FB_Bone")->setActive(Show); };
	void ShowBackArm(bool Show) { _drawable->skeleton->findBone("BF_Bone")->setActive(Show); _drawable->skeleton->findBone("BB_Bone")->setActive(Show); };

	void SetPosition(sf::Vector2i Position);
	void SetPosition(float x, float y);
	void SetAnimation(const char* Animation);

	spine::Skeleton* GetSkeleton() { return _skeleton; };

	AnimationHandler();
	AnimationHandler(const char* jsonFilepath, const char* atlasFilepath, sf::Vector2i Position = sf::Vector2i(320, 320));
	~AnimationHandler();
};

#endif