#pragma once
#include "MobyDick.h"


class BBStateComponent : public StateComponent
{

public:
	BBStateComponent(Json::Value definitionJSON);


protected:

	virtual void initializeMutuallyExclusiveStates() override;

	virtual void setState(GameObjectState newState) override final;

private:

};

