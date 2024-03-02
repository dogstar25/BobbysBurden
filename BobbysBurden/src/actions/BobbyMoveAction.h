#pragma once
#include "MobyDick.h"
#include "../GameConstants.h"

class BobbyMoveAction : public Action
{

public:
	BobbyMoveAction() = default;

	void perform(GameObject* gameObject, int direction, int strafe) override;

private:
	void _repositionEquippedItem(std::string gameObjectType, GameObject* bobbyObject);
};