#pragma once
#include "MobyDick.h"

class DisableProximityHintAction :  public Action
{
public:

	DisableProximityHintAction(Json::Value properties, GameObject* parent)
		:Action(properties, parent) {}

	void perform() override;

};

