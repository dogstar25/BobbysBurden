#pragma once

#include "MobyDick.h"

class DoorToggleAction : public Action
{

public:
	DoorToggleAction(Json::Value properties, GameObject* parent)
		:Action(properties, parent) {}

	void perform() override;


};

