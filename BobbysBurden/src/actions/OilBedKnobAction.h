#pragma once
#include "MobyDick.h"

class OilBedKnobAction : public Action
{

public:
	OilBedKnobAction(Json::Value properties, GameObject* parent)
		:Action(properties, parent) {}

	void perform(GameObject* gameObject, GameObject* gameObject2) override;

};