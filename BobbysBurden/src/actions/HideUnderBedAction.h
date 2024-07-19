#pragma once
#include "MobyDick.h"

class HideUnderBedAction : public Action
{

public:
	HideUnderBedAction(Json::Value properties, GameObject* parent)
		:Action(properties, parent) {}

	void perform(GameObject* gameObject) override;

};