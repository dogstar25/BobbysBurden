#pragma once
#include "MobyDick.h"

class TwistBedKnobAction : public Action
{

public:
	TwistBedKnobAction(Json::Value properties, GameObject* parent)
		:Action(properties, parent) {}

	void perform() override;

};