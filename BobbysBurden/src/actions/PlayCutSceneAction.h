#pragma once
#include "MobyDick.h"

class PlayCutSceneAction : public Action
{

public:
	PlayCutSceneAction(Json::Value properties, GameObject* parent)
		:Action(properties, parent) {}

	void perform(GameObject* gameObject) override;

};