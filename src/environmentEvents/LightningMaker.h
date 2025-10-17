#pragma once
#include "MobyDick.h"


const std::string LIGHTNING_FLASH_BACK = "lightningBackgroundFinal";
const std::string LIGHTNING_FLASH_MIDDLE = "lightningBackground";


class LightningMaker :   public EnvironmentEvent
{
public:
	LightningMaker() = default;
	LightningMaker(std::variant<std::string, EventLevel, float> param, Timer durationTimer);

	std::vector<std::shared_ptr<EnvironmentEvent>> perform(GameObject* gameObject) override;
	void stop(GameObject* gameObject) override;

private:
	Timer m_frequencyTimer{0.};
	EventLevel m_eventLevel{};
	float m_minimumTimeFrequency{};
	float m_maximumTimeFrequency{};


	std::vector<std::shared_ptr<EnvironmentEvent>> _createLighting(int randomSeed, GameObject* environmentObject);
	std::vector<std::shared_ptr<EnvironmentEvent>> _createLightingBolt(int randomSeed, GameObject* environmentObject);

};

