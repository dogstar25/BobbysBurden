#pragma once
#include "MobyDick.h"

class PlayCutSceneAction : public Action
{

public:
	PlayCutSceneAction(Json::Value properties)
		:Action(properties) {}

	void perform(GameObject* gameObject) override;

};