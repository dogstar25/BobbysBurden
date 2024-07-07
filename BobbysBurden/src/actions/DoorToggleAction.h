#pragma once

#include "MobyDick.h"

class DoorToggleAction : public Action
{

public:
	DoorToggleAction(Json::Value properties)
		:Action(properties) {}

	void perform(GameObject* doorObject) override;


};

