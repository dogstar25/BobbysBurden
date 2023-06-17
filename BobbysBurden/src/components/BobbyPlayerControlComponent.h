#pragma once

#include "MobyDick.h"


class AnimationComponent;
class PhysicsComponent;
class TransformComponent;
class VitalityComponent;


namespace PlayerState {
	inline constexpr int sprinting = 5;
}

class BobbyPlayerControlComponent : public PlayerControlComponent
{
public:

	BobbyPlayerControlComponent();
	BobbyPlayerControlComponent(Json::Value componentJSON);

	~BobbyPlayerControlComponent();

	void update() override;
	void postInit() override;


private:

	void _handleMovement();
	void _handleActions();
	bool _isTouchingStairs();
	void _applyStairWalkingSettings();
	void _removeStairWalkingSettings();
	std::optional<GameObject*> _doorPortalContact();

};


