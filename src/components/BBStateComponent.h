#pragma once
#include "MobyDick.h"


class BBStateComponent : public StateComponent
{

public:
	BBStateComponent(Json::Value definitionJSON, GameObject* parent);
	void update() override;
	virtual void postInit() override;
	void flipBobby();
	virtual void addState(GameObjectState state) override;
	virtual void removeState(GameObjectState state) override;
	void _setAndReconcileState(GameObjectState newState);

protected:

private:

	void _setHouseLocationContext();
	void _setOnOffStates();
	
};

