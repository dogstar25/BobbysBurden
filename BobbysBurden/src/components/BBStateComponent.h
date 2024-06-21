#pragma once
#include "MobyDick.h"


class BBStateComponent : public StateComponent
{

public:
	BBStateComponent(Json::Value definitionJSON);
	void update() override;
	void flipBobby();

protected:

	virtual void addState(GameObjectState state) override;
	virtual void removeState(GameObjectState state) override;
	void _setAndReconcileState(GameObjectState newState);

	

private:

	
};

