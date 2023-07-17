#pragma once
#include "MobyDick.h"

class TwistBedKnobAction : public Action
{

public:
	TwistBedKnobAction() = default;

	void perform(GameObject* gameObject) override;

};