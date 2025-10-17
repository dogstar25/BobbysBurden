#pragma once
#include "MobyDick.h"


class LightningWindowFlashEvent :   public EnvironmentEvent
{
public:
	LightningWindowFlashEvent() = default;
	LightningWindowFlashEvent(std::variant<std::string, EventLevel, float> param, Timer durationTimer);

	std::vector<std::shared_ptr<EnvironmentEvent>> perform(GameObject* gameObject) override;
	void stop(GameObject* gameObject) override;

private:
	EventLevel m_eventLevel{};

	void _flipWindowFlash(GameObject* environmentObject, GameObjectState newState);

};

