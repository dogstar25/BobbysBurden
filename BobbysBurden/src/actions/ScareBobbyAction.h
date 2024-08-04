#pragma once
#include "MobyDick.h"

class ScareBobbyAction : public Action
{

public:
	ScareBobbyAction(Json::Value properties, GameObject* parent)
		:Action(properties, parent) {}

	void perform(GameObject* gameObject) override;

};