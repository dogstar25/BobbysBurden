#pragma once
#include "MobyDick.h"

class OilBedKnobAction : public Action
{

public:
	OilBedKnobAction() = default;

	void perform(GameObject* gameObject, GameObject* gameObject2) override;

};