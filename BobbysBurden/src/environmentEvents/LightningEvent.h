#pragma once
#include "MobyDick.h"
#include "../GameConstants.h"


class LightningEvent :   public EnvironmentEvent
{
public:
	LightningEvent() = default;
	LightningEvent(std::variant<std::string, EventLevel, float> param, Timer durationTimer);

	std::vector<std::shared_ptr<EnvironmentEvent>> perform(GameObject* gameObject) override;
	void stop(GameObject* gameObject) override;
	EventLevel eventLevel() { return m_eventLevel; }

private:
	EventLevel m_eventLevel{};
	LightningLayor m_layer{ LightningLayor::MIDDLE };
	std::optional<std::shared_ptr<GameObject>> m_lightningOverlay;

	void _flipWindowFlash(GameObject* environmentObject, GameObjectState newState);

};

