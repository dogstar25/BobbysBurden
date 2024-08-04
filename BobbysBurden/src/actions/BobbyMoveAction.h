#pragma once
#include "MobyDick.h"
#include "../GameConstants.h"

class BobbyMoveAction : public Action
{

public:
	BobbyMoveAction(Json::Value properties, GameObject* parent)
		:Action(properties, parent) {}

	void perform(GameObject* gameObject, int direction, int strafe) override;

private:
	void _repositionEquippedItem(std::string gameObjectType, GameObject* bobbyObject);
	SDL_Point _determineScaryDirection(GameObject* playerObject);
};