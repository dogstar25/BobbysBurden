#pragma once
#include "MobyDick.h"

class HideUnderBedAction : public Action
{

public:
	HideUnderBedAction() = default;

	void perform(GameObject* gameObject, GameObject* gameObject2) override;
	bool isApplicable(GameObject* gameObject, GameObject* gameObject2) override;

};