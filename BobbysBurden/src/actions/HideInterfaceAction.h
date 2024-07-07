#pragma once
#include "MobyDick.h"

class HideInterfaceAction :  public Action
{
public:

	HideInterfaceAction(Json::Value properties)
		:Action(properties) {}

	void perform(GameObject* gameObject) override;

};

