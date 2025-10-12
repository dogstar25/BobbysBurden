#pragma once
#include "MobyDick.h"

class PlayPhonographAction : public Action
{

public:
	PlayPhonographAction(Json::Value properties, GameObject* parent)
		:Action(properties, parent) {}

	void perform() override;

private:
	void _handleRecord(std::shared_ptr<GameObject> record);

};