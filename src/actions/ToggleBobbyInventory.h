#pragma once

#include "MobyDick.h"

class ToggleBobbyInventory : public Action
{

public:
	ToggleBobbyInventory(Json::Value properties, GameObject* parent)
		:Action(properties, parent) {}

	void perform() override;


};

