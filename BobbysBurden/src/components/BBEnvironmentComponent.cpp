#include "BBEnvironmentComponent.h"
#include "../GameConstants.h"
#include "../BBEnviornmentEvents.h"

extern std::unique_ptr<Game> game;

BBEnvironmentComponent::BBEnvironmentComponent(Json::Value componentJSON) :
	EnvironmentComponent(ComponentTypes::ENVIRONMENT_COMPONENT)
{

	m_enviornmentCycle.resize(enviornmentSequence::CYCLE_COUNT);
	m_enviornmentCycle[enviornmentSequence::APPROACHING_STORM].assign_range(stormCycleDistantApproaching);
	m_enviornmentCycle[enviornmentSequence::CLOSE_STORM].assign_range(stormCycleCloseStorm);




}

void BBEnvironmentComponent::postInit()
{

	//Get the main house overlay object
	const auto& houseOverlay = parent()->parentScene()->getFirstGameObjectByType("HOUSE_OVERLAY");
	const auto& houseMaskOverlayComponent = houseOverlay.value()->getComponent<MaskedOverlayComponent>(ComponentTypes::MASKED_OVERLAY_COMPONENT);

	//Create a rain emitter object
	auto rainEmitter = parent()->parentScene()->createGameObject("PARTICLE_EMITTER_RAIN", -1.0F, -1.0F, 0.F, parent()->parentScene(), GameLayer::MAIN);
	rainEmitter->disableRender();
	rainEmitter->disableUpdate();
	houseMaskOverlayComponent->addOverlayObject(rainEmitter);

	//Create lightning overlay
	auto lightingFilter = parent()->parentScene()->createGameObject("LIGHTNING_FOREGROUND_FILTER_1", -1.0F, -1.0F, 0.F, parent()->parentScene(), GameLayer::MAIN);
	houseMaskOverlayComponent->addOverlayObject(lightingFilter);

	

}

void BBEnvironmentComponent::setParent(GameObject* gameObject)
{
	//Call base component setParent
	Component::setParent(gameObject);

}

void BBEnvironmentComponent::update()
{


	//if (testLightningTimer.hasMetTargetDuration()) {


	//	const auto& lightningOverlay = parent()->parentScene()->getFirstGameObjectByName("lightningBackgroundFinal");
	//	if (lightningOverlay.value()->hasState(GameObjectState::DISABLED_RENDER)) {

	//		lightningOverlay.value()->removeState(GameObjectState::DISABLED_RENDER);

	//	}
	//	else {

	//		lightningOverlay.value()->addState(GameObjectState::DISABLED_RENDER);

	//	}



	//}


	const auto& soundComponent = parent()->getComponent<SoundComponent>(ComponentTypes::SOUND_COMPONENT);

	bool allComplete = true;

	//Find the first sequnce object that is not already complete or that has started and should continue
	for (auto& event : m_enviornmentCycle[m_currentSequence]) {

		if (event.status != EventStatus::COMPLETE) {

			allComplete = false;

			switch (event.environmentEventType)
			{
				case EnvironmentEventType::LIGHTNING_FLASH_BACK:
				case EnvironmentEventType::LIGHTNING_FLASH_MIDDLE:
				case EnvironmentEventType::LIGHTNING_FLASH_FRONT:
					_lightningflash(event);
					break;
				case EnvironmentEventType::LIGHTNING_BOLT_1_BACK:
					break;
				case EnvironmentEventType::LIGHTNING_BOLT_1_MIDDLE:
					break;
				case EnvironmentEventType::LIGHTNING_BOLT_1_FRONT:
					break;
				case EnvironmentEventType::THUNDER_RUMBLE_1:
					soundComponent->playSound("THUNDER_RUMBLE_1");
					event.status = EventStatus::COMPLETE;
					break;
				case EnvironmentEventType::THUNDER_RUMBLE_2:
					soundComponent->playSound("THUNDER_RUMBLE_2");
					event.status = EventStatus::COMPLETE;
					break;
				case EnvironmentEventType::THUNDER_RUMBLE_3:
					break;
				case EnvironmentEventType::THUNDER_BOOM_1:
					break;
				case EnvironmentEventType::THUNDER_BOOM_2:
					break;
				case EnvironmentEventType::RAIN_LIGHT:
				case EnvironmentEventType::RAIN_MEDIUM:
				case EnvironmentEventType::RAIN_HEAVY:
					_rain(event);
					event.status = EventStatus::COMPLETE;
					break;
				case EnvironmentEventType::WINDDOW_FLASH:
					break;
				case EnvironmentEventType::WAIT_EVENT:

					if (event.durationTimer.isFirstTime() == true) {
						event.durationTimer.reset();
						event.status = EventStatus::IN_PROGRESS;
					}
					else if(event.durationTimer.hasMetTargetDuration()) {
						event.status = EventStatus::COMPLETE;
					}

					break;

				default:
					break;
			}

			break;

		}


	}

	//If all events are complete, then reset them and see if we should repeat
	//If not repeating, then progress to next event sequence and if this is last event sequence then
	//reset to first sequence
	if (allComplete) {

		_resetSequence(m_currentSequence);
		enviornmentSequenceRepeatCount[m_currentSequence]++;
		if (enviornmentSequenceRepeatCount[m_currentSequence] >= enviornmentSequenceRepeat[m_currentSequence]) {

			if (m_currentSequence < enviornmentSequence::CYCLE_COUNT) {

				m_currentSequence++;
			}
			else {
				m_currentSequence = 0;
			}

		}

	}

}

void BBEnvironmentComponent::_resetSequence(int sequence)
{

	for (auto& event : m_enviornmentCycle[m_currentSequence]) {

		event.status = EventStatus::IDLE;
	}

}


void BBEnvironmentComponent::_rain(EnvironmentEvent& event)
{

	const auto& rainEmitter = parent()->parentScene()->getFirstGameObjectByType("PARTICLE_EMITTER_RAIN");
	rainEmitter.value()->enableRender();
	rainEmitter.value()->enableUpdate();
	const auto& rainParticleComponent = rainEmitter.value()->getComponent<ParticleComponent>(ComponentTypes::PARTICLE_COMPONENT);

	switch (event.environmentEventType) {

		case EnvironmentEventType::RAIN_LIGHT:

			rainParticleComponent->setParticleEffectSpawnCount("RAIN", 20, 50);
			rainParticleComponent->setParticleEffectEmitAngle("RAIN", 90.0F, 90.0F);
			rainParticleComponent->setParticleEffectForce("RAIN", 50.0F, 70.0F);
			rainParticleComponent->setEmissionInterval(0.5);

			break;
		case EnvironmentEventType::RAIN_MEDIUM:
			break;
		case EnvironmentEventType::RAIN_HEAVY:
			break;
		default:
			break;

	}

}

void BBEnvironmentComponent::_lightningflash(EnvironmentEvent& event)
{
	std::string gameObjectName{};
	if (event.environmentEventType == EnvironmentEventType::LIGHTNING_FLASH_BACK) {
		gameObjectName = "lightningBackgroundFinal";
	}
	else if (event.environmentEventType == EnvironmentEventType::LIGHTNING_FLASH_MIDDLE) {
		gameObjectName = "lightningBackground";
	}
	else if (event.environmentEventType == EnvironmentEventType::LIGHTNING_FLASH_FRONT) {

		//This is tied to the house overlay and is a little special
		_handlelightingFront(event);
	}

	//Expose lighting flash
	if (event.durationTimer.isFirstTime()) {

		const auto& lightningOverlay = parent()->parentScene()->getFirstGameObjectByName(gameObjectName);
		lightningOverlay.value()->removeState(GameObjectState::DISABLED_RENDER);
		event.status = EventStatus::IN_PROGRESS;
		event.durationTimer.reset();
	}

	//Hide lighting flash
	if (event.durationTimer.hasMetTargetDuration()) {

		const auto& lightningOverlay = parent()->parentScene()->getFirstGameObjectByName(gameObjectName);
		lightningOverlay.value()->addState(GameObjectState::DISABLED_RENDER);
		event.status = EventStatus::COMPLETE;
	}

}

void BBEnvironmentComponent::_handlelightingFront(EnvironmentEvent& event)
{

	const auto& houseOverlayObject = parent()->parentScene()->getFirstGameObjectByType("HOUSE_OVERLAY");
	const auto& maskOverlayComponent = houseOverlayObject.value()->getComponent<MaskedOverlayComponent>(ComponentTypes::MASKED_OVERLAY_COMPONENT);
	const auto& lightningFilterObject = maskOverlayComponent->getOverlayObject("LIGHTNING_FOREGROUND_FILTER_1");

	//Expose lighting flash
	if (event.durationTimer.isFirstTime()) {

		lightningFilterObject.value()->removeState(GameObjectState::DISABLED_RENDER);
		event.status = EventStatus::IN_PROGRESS;
		event.durationTimer.reset();
	}

	//Hide lighting flash
	if (event.durationTimer.hasMetTargetDuration()) {

		lightningFilterObject.value()->addState(GameObjectState::DISABLED_RENDER);
		event.status = EventStatus::COMPLETE;
	}


}
