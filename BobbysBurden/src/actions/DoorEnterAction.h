#pragma once
#include "MobyDick.h"

class DoorEnterAction : public Action
{

public:
	DoorEnterAction(Json::Value properties)
		:Action(properties) {}

	void perform(GameObject* interactingObject, GameObject* interactionObject) override;
	void perform(GameObject* interactionObject) override;


};

