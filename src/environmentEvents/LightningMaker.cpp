#include "LightningMaker.h"
#include "LightningEvent.h"


//extern std::unique_ptr<Game> game;

LightningMaker::LightningMaker(std::variant<std::string, EventLevel, float> param, Timer durationTimer) :
	EnvironmentEvent(durationTimer)
{

	m_eventLevel = std::get<EventLevel>(param);

	if (m_eventLevel == EventLevel::MILD) {
		m_minimumTimeFrequency = 2.0;
		m_maximumTimeFrequency = 3.0;
	}
	else if (m_eventLevel == EventLevel::MODERATE) {
		m_minimumTimeFrequency = 1.0;
		m_maximumTimeFrequency = 2.0;
	}
	else if (m_eventLevel == EventLevel::INTENSE) {
		m_minimumTimeFrequency = 0.5;
		m_maximumTimeFrequency = 1.5;
	}

}


std::vector<std::shared_ptr<EnvironmentEvent>> LightningMaker::perform(GameObject* environmentObject)
{

	std::vector<std::shared_ptr<EnvironmentEvent>> newEvents{};

	if (m_status == EventStatus::IDLE) {
		m_durationTimer.reset();
		m_status = EventStatus::IN_PROGRESS;
	}

	if (m_frequencyTimer.timeElapsed().count() > m_minimumTimeFrequency) {

		int randomNumber = std::rand() % 10;
		m_frequencyTimer.reset();

		//If we are at the maximum amount of time passed, then create lighting
		if (m_frequencyTimer.timeElapsed().count() > m_maximumTimeFrequency) {

			newEvents = _createLighting(randomNumber, environmentObject);
			m_frequencyTimer.reset();
			
		}
		//If we are in the middle of the time window, then make a random decision to make lightning
		//If we decide NOT to , still reset the timer
		else {

			
			//33% chance
			if (randomNumber <= 2) {

				newEvents = _createLighting(randomNumber, environmentObject);

			}

		}

		//If we have not created a lighting flash event then consider making a lightning bolt event
		if(newEvents.empty() == true){

			//33% chance
			if (randomNumber >=8) {

				newEvents = _createLightingBolt(randomNumber, environmentObject);
			}
			
		}

	}

	return newEvents;

}

void LightningMaker::stop(GameObject* gameObject)
{


}

std::vector<std::shared_ptr<EnvironmentEvent>> LightningMaker::_createLighting(int randomSeed, GameObject* environmentObject)
{

	std::vector<std::shared_ptr<EnvironmentEvent>> newEvents{};

	float timerDuration{};
	//Calculate a random duration
	if (randomSeed == 0) {
		timerDuration = 0.1f;
	}
	else if (randomSeed == 1) {
		timerDuration = 0.25f;
	}
	else if (randomSeed == 2) {
		timerDuration = 0.75f;
	}
	else {
		timerDuration = 1.0f;
	}

	//Create a lighting flash event
	std::shared_ptr<LightningEvent> lightningEventvent = std::dynamic_pointer_cast<LightningEvent>(
		game->environmentEventFactory()->create("lightningEvent", m_eventLevel, Timer(timerDuration))
	);
	newEvents.push_back(lightningEventvent);

	//If this is a moderate or intense level flash, then all create a window flash event 50% of the time
	if (lightningEventvent->eventLevel() == EventLevel::MODERATE || 
		lightningEventvent->eventLevel() == EventLevel::INTENSE) {

		//50% chance
		int randomNumber = std::rand() % 2;
		if (randomNumber == 0) {
			auto event = game->environmentEventFactory()->create("lightningWindowFlashEvent", m_eventLevel, Timer(timerDuration));
			newEvents.push_back(event);
		}

	}



	return newEvents;

}

std::vector<std::shared_ptr<EnvironmentEvent>> LightningMaker::_createLightingBolt(int randomSeed, GameObject* environmentObject)
{

	std::vector<std::shared_ptr<EnvironmentEvent>> newEvents{};


	auto event = game->environmentEventFactory()->create("lightningBoltEvent", m_eventLevel, Timer(1));
	newEvents.push_back(event);


	return newEvents;

}
