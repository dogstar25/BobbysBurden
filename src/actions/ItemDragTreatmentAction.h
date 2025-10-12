#pragma once
#include "MobyDick.h"

class ItemDragTreatmentAction : public Action
{
public:
	ItemDragTreatmentAction(Json::Value properties, GameObject* parent)
		:Action(properties, parent) {}

	void perform() override;


};

