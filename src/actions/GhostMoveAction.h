#pragma once
#include "MobyDick.h"
#include "../GameConstants.h"

class GhostMoveAction : public DefaultMoveAction
{

public:
	GhostMoveAction(Json::Value properties, GameObject* parent)
		:DefaultMoveAction(properties, parent) {}

	void perform(b2Vec2 trajectory) override;

};