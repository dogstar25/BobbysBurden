#pragma once
#include "MobyDick.h"

class BBEnvironmentComponent : public EnvironmentComponent
{

public:
	BBEnvironmentComponent(Json::Value definitionJSON);

	virtual void update() override;
	virtual void postInit() override;
	virtual void setParent(GameObject* gameObject) override;

protected:


private:

	bool m_isStorming{};

	Timer testLightningTimer{ 1.0, true };
	Timer testLightningTimer2{ 1.2, true };
	Timer testLightningTimer3{ 1.4, true };
	

	


};

