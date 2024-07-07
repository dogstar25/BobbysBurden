#pragma once

#include "MobyDick.h"

class ToggleBobbyInventory : public Action
{

public:
	ToggleBobbyInventory(Json::Value properties)
		:Action(properties) {}

	void perform(GameObject* doorObject) override;


};

