#pragma once
#include "MobyDick.h"

class GhostDoorEnterAction : public Action
{

public:
	GhostDoorEnterAction(Json::Value properties, GameObject* parent)
		:Action(properties,parent) {}

	void perform() override;


};

