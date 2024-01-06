#pragma once
#include "MobyDick.h"


class BBStateComponent : public StateComponent
{

public:
	BBStateComponent(Json::Value definitionJSON);


protected:

	virtual void addState(int state) override;
	void _setAndReconcileState(int newState);
	bool _hasTransitionDuration(int state);

private:

	

};

