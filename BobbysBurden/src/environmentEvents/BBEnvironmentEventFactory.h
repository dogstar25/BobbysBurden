#pragma once
#include "MobyDick.h"

class BBEnvironmentEventFactory : public EnvironmentEventFactory {



public:

	virtual std::shared_ptr<EnvironmentEvent> create(std::string eventType, std::variant<std::string, EventLevel, float> param, Timer durationTimer);


private:




};
