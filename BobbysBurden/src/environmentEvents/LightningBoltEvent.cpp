#include "LightningBoltEvent.h"
#include "../BBGame.h"
#include "../BBContextManager.h"


extern std::unique_ptr<Game> game;


LightningBoltEvent::LightningBoltEvent(std::variant<std::string, EventLevel, float> param, Timer durationTimer) :
	EnvironmentEvent(durationTimer)
{

	m_eventLevel = std::get<EventLevel>(param);

}


std::vector<std::shared_ptr<EnvironmentEvent>> LightningBoltEvent::perform(GameObject* environmentObject)
{
	std::vector<std::shared_ptr<EnvironmentEvent>> newEvents{};
	GameLayer gameLayer{ GameLayer::BACKGROUND_5 };
	std::string lightningBoltObjectType{};

	//Show Lighting Flash
	if (m_status == EventStatus::IDLE) {

		m_status = EventStatus::IN_PROGRESS;
		m_durationTimer.reset();


		int randomNumber = std::rand() % 10;
		std::optional<b2Vec2> sizeOverride{};

		//Pick a layer back, middle, front for the bolt to display
		LightningLayor layer = _determineLayer();

		//Pick a horizontal location for the bolt to display
		SDL_Point location = _determineLocation(layer);

		//Translate lightning layer to game scene layer
		if (layer == LightningLayor::BACK) {

			gameLayer = GameLayer::BACKGROUND_FINAL;
		}
		else if (layer == LightningLayor::MIDDLE) {

			gameLayer = GameLayer::BACKGROUND_1;
		}
		else if (layer == LightningLayor::FRONT) {

			sizeOverride = {600, 2000};
			gameLayer = GameLayer::FOREGROUND_FINAL;
		}

		//50% chance for either of the 2 lightning bolt images
		if (randomNumber <=4 ) {
			lightningBoltObjectType = "LIGHTNING_BOLT_1";
		}
		else {
			lightningBoltObjectType = "LIGHTNING_BOLT_2";
		}


		m_lightningBoltObject = environmentObject->parentScene()->addGameObject(lightningBoltObjectType, nullptr, gameLayer, location.x, location.y );
		if (sizeOverride.has_value()) {
			m_lightningBoltObject.value()->setSize(sizeOverride.value());
		}

		//Create a thunder strike soundEvent
		std::shared_ptr<EnvironmentEvent> thunderSoundEvent = _createThunderStrikeSound(layer);
		newEvents.push_back(thunderSoundEvent);

	}

	return newEvents;

}

LightningLayor LightningBoltEvent::_determineLayer()
{
	LightningLayor layer{ LightningLayor::BACK };

	int randomNumber = std::rand() % 10;

	if (m_eventLevel == EventLevel::MODERATE) {

		if (randomNumber <= 3) {

			layer = LightningLayor::BACK;

		}
		else {
			layer = LightningLayor::MIDDLE;
		}

	}
	else if (m_eventLevel == EventLevel::INTENSE) {

		if (randomNumber <= 2) {

			layer = LightningLayor::BACK;

		}
		else if (randomNumber <= 8) {
			layer = LightningLayor::MIDDLE;
		}
		else {
			layer = LightningLayor::FRONT;
		}

	}

	return layer;

}

SDL_Point LightningBoltEvent::_determineLocation(LightningLayor layer)
{
	//The X for this location will be whatever our current house position is in
	
	SDL_Point location = static_cast<BBContextManager*>(game->contextMananger().get())->currentHousePosition();

	int randomNumberForLeftRight = std::rand() % 10;

	//If this is the back or middle layer, pick a location that is to left or right of the house
	if (layer == LightningLayor::BACK || layer == LightningLayor::MIDDLE) {

		//50% left or right
		if (randomNumberForLeftRight <= 4) {

			int randomNumberForLocation = util::generateRandomNumber(m_horizontalRangeLeft.x, m_horizontalRangeLeft.y);
			location.x = randomNumberForLocation;

		}
		else {

			int randomNumberForLocation = util::generateRandomNumber(m_horizontalRangeRight.x, m_horizontalRangeRight.y);
			location.x = randomNumberForLocation;

		}

	}
	else {

		int randomNumberForLocation = util::generateRandomNumber(m_fullRange.x, m_fullRange.y);
		location.x = randomNumberForLocation;

	}

	return location;

}

std::shared_ptr<EnvironmentEvent> LightningBoltEvent::_createThunderStrikeSound(LightningLayor layer)
{

	int randomeNumber = std::rand() % 10;
	std::string thunderSoundId{};

	//If bolt is in far back, then tunder strike 40% of the time
	//if (layer == LightningLayor::BACK) {

	//	if (randomeNumber <=3) {

	//		if (randomeNumber <=1) {
	//			thunderSoundId = "THUNDER_BOOM_1";
	//		}
	//		else {
	//			thunderSoundId = "THUNDER_BOOM_2";
	//		}

	//	}
	//}
	////If bolt is in middle, then tunder strike 60% of the time
	//else if (layer == LightningLayor::MIDDLE) {

	//	if (randomeNumber <= 5) {

	//		if (randomeNumber <= 1) {
	//			thunderSoundId = "THUNDER_BOOM_1";
	//		}
	//		else if (randomeNumber <= 4) {
	//			thunderSoundId = "THUNDER_BOOM_2";
	//		}
	//		else {
	//			thunderSoundId = "THUNDER_BOOM_3";
	//		}

	//	}

	//}
	//If bolt is in front, then tunder strike 70% of the time
	if (layer == LightningLayor::FRONT) {

		if (randomeNumber <= 3) {

			if (randomeNumber <= 1) {
				thunderSoundId = "THUNDER_BOOM_3";
			}
			else {
				thunderSoundId = "THUNDER_BOOM_4";
			}

		}

	}

	std::shared_ptr<EnvironmentEvent> event = game->environmentEventFactory()->create("soundEvent", thunderSoundId, Timer(.01));

	return event;
}

void LightningBoltEvent::stop(GameObject* environmentObject)
{

	//Hide lighting flash
	if (m_durationTimer.hasMetTargetDuration()) {

		//if (m_lightningBoltObject.has_value()) {
		//	m_lightningBoltObject.value()->setRemoveFromWorld(true);
		//}
		m_status = EventStatus::COMPLETE;

	}

}

