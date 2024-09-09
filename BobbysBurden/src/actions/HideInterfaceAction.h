#pragma once
#include "MobyDick.h"

class HideInterfaceAction :  public Action
{
public:

	HideInterfaceAction(Json::Value properties, GameObject* parent)
		:Action(properties, parent) {}

	void perform() override;

};

