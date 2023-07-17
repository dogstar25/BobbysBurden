#pragma once
#include "MobyDick.h"

class HideUnderBedAction : public Action
{

public:
	HideUnderBedAction() = default;

	void perform(GameObject* gameObject) override;

};