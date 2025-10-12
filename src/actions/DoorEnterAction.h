#pragma once
#include "MobyDick.h"

class DoorEnterAction : public Action
{

public:
	DoorEnterAction(Json::Value properties, GameObject* parent)
		:Action(properties,parent) {}

	void perform() override;


};

