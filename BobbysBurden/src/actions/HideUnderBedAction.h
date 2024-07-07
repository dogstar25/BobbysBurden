#pragma once
#include "MobyDick.h"

class HideUnderBedAction : public Action
{

public:
	HideUnderBedAction(Json::Value properties)
		:Action(properties) {}

	void perform(GameObject* gameObject) override;

};