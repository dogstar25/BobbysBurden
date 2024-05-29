#pragma once
#include "MobyDick.h"
#include "../GameConstants.h"

class LightningBoltEvent :   public EnvironmentEvent
{
public:
	LightningBoltEvent() = default;
	LightningBoltEvent(std::variant<std::string, EventLevel, float> param, Timer durationTimer);

	std::vector<std::shared_ptr<EnvironmentEvent>> perform(GameObject* gameObject) override;
	void stop(GameObject* gameObject) override;
	EventLevel eventLevel() { return m_eventLevel; }

private:
	EventLevel m_eventLevel{};
	std::optional<GameObject*> m_lightningBoltObject;

	LightningLayor _determineLayer();
	SDL_Point _determineLocation(LightningLayor layer);
	std::shared_ptr<EnvironmentEvent> _createThunderStrikeSound(LightningLayor layer);

	//These are the possible Y positions where we can see the lightning bolt
	SDL_Point m_horizontalRangeLeft{2,10};
	SDL_Point m_horizontalRangeRight{ 62,72 };
	SDL_Point m_fullRange{ 2,72 };


};

