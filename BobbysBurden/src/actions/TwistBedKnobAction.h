#pragma once
#include "MobyDick.h"

class TwistBedKnobAction : public Action
{

public:
	TwistBedKnobAction(Json::Value properties)
		:Action(properties) {}

	void perform(GameObject* gameObject) override;

};