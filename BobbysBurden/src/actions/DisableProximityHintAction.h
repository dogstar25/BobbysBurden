#pragma once
#include "MobyDick.h"

class DisableProximityHintAction :  public Action
{
public:

	DisableProximityHintAction(Json::Value properties)
		:Action(properties) {}

	void perform(GameObject* gameObject) override;

};

