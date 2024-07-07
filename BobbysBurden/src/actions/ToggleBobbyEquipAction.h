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

	ToggleBobbyEquipAction(Json::Value properties)
		:Action(properties) {}

	void perform(GameObject* doorObject) override;

private:
	void _disableCandle(GameObject* gameObject);
	void _enableCandle(GameObject* gameObject);


};

