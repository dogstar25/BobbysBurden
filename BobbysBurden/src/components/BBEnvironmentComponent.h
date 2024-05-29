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

	virtual void _applyEventInstructions(int sequenmce) override;

private:

	void _lightningflash(EnvironmentEvent& event);
	void _playBackgroundTrack(EnvironmentEvent& event, std::string track);
	void _handlelightingFront(EnvironmentEvent& event);
	void _rain(EnvironmentEvent& event);
	void _resetSequence(int sequence);


	



	



	


};

