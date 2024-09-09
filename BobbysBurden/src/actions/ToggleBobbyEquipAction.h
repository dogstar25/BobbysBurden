#pragma once

#include "MobyDick.h"


enum class candleLocation {
	RIGHT,
	LEFT,
	UP,
	DOWN
};

class ToggleBobbyEquipAction : public Action
{

public:

	ToggleBobbyEquipAction(Json::Value properties, GameObject* parent)
		:Action(properties, parent) {}

	void perform() override;

private:
	void _disableCandle(GameObject* gameObject);
	void _enableCandle(GameObject* gameObject);


};

