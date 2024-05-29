#include "BBEnvironmentComponent.h"
#include "../GameConstants.h"
#include "../BBEnvironmentEvents.h"

extern std::unique_ptr<Game> game;

BBEnvironmentComponent::BBEnvironmentComponent(Json::Value componentJSON) :
	EnvironmentComponent(ComponentTypes::ENVIRONMENT_COMPONENT)
{

	m_currentCycleInstructions = environmentCycle;
	startCycle();

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

void BBEnvironmentComponent::_applyEventInstructions(int sequence)
{


	for (const auto& instruction : m_currentCycleInstructions[sequence]) {

		auto event = game->environmentEventFactory()->create(instruction.id, instruction.param, instruction.durationTimer);
		m_events.push_back(event);

	}

	//for (const auto& instruction : m_currentCycleInstructions[sequence]) {

	//	if (instruction.id == "lightningMaker") {

	//		auto event = game->environmentEventFactory()->create(instruction.id, instruction.param, instruction.durationTimer);
	//		m_events.push_back(event);

	//	}
	//	else {
	//		EnvironmentComponent::_applyEventInstructions(sequence);
	//	}

	//}

}


void BBEnvironmentComponent::setParent(GameObject* gameObject)
{
	//Call base component setParent
	Component::setParent(gameObject);

	

}

void BBEnvironmentComponent::update()
{

	EnvironmentComponent::update();


}

//void BBEnvironmentComponent::_rain(EnvironmentEvent& event)
//{
//
//	const auto& rainEmitter = parent()->parentScene()->getFirstGameObjectByType("PARTICLE_EMITTER_RAIN");
//	rainEmitter.value()->enableRender();
//	rainEmitter.value()->enableUpdate();
//	const auto& rainParticleComponent = rainEmitter.value()->getComponent<ParticleComponent>(ComponentTypes::PARTICLE_COMPONENT);
//
//	switch (event.environmentEventType) {
//
//		case EnvironmentEventType::RAIN_LIGHT:
//
//			rainParticleComponent->setParticleEffectSpawnCount("RAIN", 20, 50);
//			rainParticleComponent->setParticleEffectEmitAngle("RAIN", 90.0F, 90.0F);
//			rainParticleComponent->setParticleEffectForce("RAIN", 50.0F, 70.0F);
//			rainParticleComponent->setEmissionInterval(0.5);
//
//			break;
//		case EnvironmentEventType::RAIN_MEDIUM:
//			break;
//		case EnvironmentEventType::RAIN_HEAVY:
//			break;
//		default:
//			break;
//
//	}
//
//}

