#pragma once
#include "MobyDick.h"


class BBStateComponent : public StateComponent
{

public:
	BBStateComponent(Json::Value definitionJSON);


protected:

	virtual void addState(int state) override;

private:

	bool _checkTransition(int state) override;

};

