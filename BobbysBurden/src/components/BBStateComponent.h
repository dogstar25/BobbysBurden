#pragma once
#include "MobyDick.h"


class BBStateComponent : public StateComponent
{

public:
	BBStateComponent(Json::Value definitionJSON);


protected:

	virtual void addState(GameObjectState state) override;
	void _setAndReconcileState(GameObjectState newState);

private:

	
};

