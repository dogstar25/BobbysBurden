#pragma once
#include "MobyDick.h"

class ShowInterfaceAction :  public Action
{
public:

	ShowInterfaceAction(Json::Value properties, GameObject* parent)
		:Action(properties, parent) {}

	void perform() override;

};

