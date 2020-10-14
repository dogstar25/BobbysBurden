#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include <string>
#include <map>
#include <memory>
#include <json/json.h>

#include "Component.h"
#include "../Animation.h"

class TransformComponent;

class AnimationComponent : public Component
{
public:
	AnimationComponent() {};
	AnimationComponent(Json::Value definitionJSON);
	~AnimationComponent();

	void update() override;
	SDL_Rect* getCurrentAnimationTextureRect();
	SDL_Texture* getCurrentAnimationTexture();
	void animate(int animationState, int animationMode);

	void setCurrentAnimationState(int animationState) { m_currentAnimationState = animationState; }
	int currentAnimationState() { return m_currentAnimationState; }

	std::array<std::shared_ptr<Animation>, 5>& animations() { return m_animations; }

private:

	int m_currentAnimationState{ 0 };
	int m_currentAnimationMode{ ANIMATE_ONE_TIME };
	int m_defaultAnimationState{ 0 };

	std::array<std::shared_ptr<Animation>, 5> m_animations;
};

#endif