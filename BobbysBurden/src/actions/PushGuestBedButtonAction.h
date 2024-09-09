#pragma once
#include "MobyDick.h"

class PushGuestBedButtonAction : public Action
{

public:
	PushGuestBedButtonAction(Json::Value properties, GameObject* parent)
		:Action(properties, parent) {}

	void perform() override;

};