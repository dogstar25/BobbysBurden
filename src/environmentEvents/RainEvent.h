#pragma once
#include "MobyDick.h"


class RainEvent :   public EnvironmentEvent
{
public:
	RainEvent() = default;
	RainEvent(std::variant<std::string, EventLevel, float> param, Timer durationTimer);

	std::vector<std::shared_ptr<EnvironmentEvent>> perform(GameObject* gameObject) override;
	void stop(GameObject* gameObject) override;

private:
	EventLevel m_eventLevel{};


};

