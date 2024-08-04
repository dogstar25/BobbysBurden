#pragma once
#include "MobyDick.h"

class SpiderDeployAction : public Action
{

public:
	SpiderDeployAction(Json::Value properties, GameObject* parent)
		:Action(properties, parent) {}

	void perform(GameObject* gameObject) override;

};