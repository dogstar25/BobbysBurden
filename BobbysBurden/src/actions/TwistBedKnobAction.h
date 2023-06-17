#pragma once
#include "MobyDick.h"

class TwistBedKnobAction : public Action
{

public:
	TwistBedKnobAction() = default;

	void perform(GameObject* gameObject, GameObject* gameObject2) override;
	bool isApplicable(GameObject* gameObject, GameObject* gameObject2) override;

};