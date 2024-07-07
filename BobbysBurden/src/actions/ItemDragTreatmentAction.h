#pragma once
#include "MobyDick.h"

class ItemDragTreatmentAction : public Action
{
public:
	ItemDragTreatmentAction(Json::Value properties)
		:Action(properties) {}

	void perform(GameObject* gameObject) override;


};

