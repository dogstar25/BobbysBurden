#pragma once
#include "MobyDick.h"

class DisableProximityHintAction :  public Action
{
public:
	void perform(GameObject* gameObject) override;

};

