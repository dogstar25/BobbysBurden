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

	BobbyPlayerControlComponent()=default;
	BobbyPlayerControlComponent(Json::Value componentJSON, GameObject* parent);

	~BobbyPlayerControlComponent();

	void update() override;
	void postInit() override;


private:

	void _handleMovement();
	void _handleActions();
	void _applyStairWalkingSettings();
	void _removeStairWalkingSettings();

};


