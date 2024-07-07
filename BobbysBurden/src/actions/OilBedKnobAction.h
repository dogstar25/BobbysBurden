#pragma once
#include "MobyDick.h"

class OilBedKnobAction : public Action
{

public:
	OilBedKnobAction(Json::Value properties)
		:Action(properties) {}

	void perform(GameObject* gameObject, GameObject* gameObject2) override;

};