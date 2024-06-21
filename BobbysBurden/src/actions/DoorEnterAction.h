#pragma once
#include "MobyDick.h"

class DoorEnterAction : public Action
{

	void perform(GameObject* interactingObject, GameObject* interactionObject) override;
	void perform(GameObject* interactionObject) override;


};

