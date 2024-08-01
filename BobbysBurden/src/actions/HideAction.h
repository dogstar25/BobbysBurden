#pragma once
#include "MobyDick.h"

class HideAction : public Action
{

public:
	HideAction(Json::Value properties, GameObject* parent)
		:Action(properties, parent) {}

	void perform(GameObject* gameObject) override;

};