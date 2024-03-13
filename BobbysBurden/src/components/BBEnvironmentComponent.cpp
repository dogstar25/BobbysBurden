#include "BBEnvironmentComponent.h"

extern std::unique_ptr<Game> game;

BBEnvironmentComponent::BBEnvironmentComponent(Json::Value componentJSON) :
	EnvironmentComponent(ComponentTypes::ENVIRONMENT_COMPONENT)
{


}

void BBEnvironmentComponent::postInit()
{

	//Get the main house overlay object
	const auto& houseOverlay = parent()->parentScene()->getFirstGameObjectByType("HOUSE_OVERLAY");
	const auto& houseMaskOverlayComponent = houseOverlay.value()->getComponent<MaskedOverlayComponent>(ComponentTypes::MASKED_OVERLAY_COMPONENT);

	//Create a rain emitter object
	auto rainEmitter = parent()->parentScene()->createGameObject("PARTICLE_EMITTER_RAIN", -1.0F, -1.0F, 0.F, parent()->parentScene(), GameLayer::MAIN);
	houseMaskOverlayComponent->addOverlayObject(rainEmitter);

	//Create lightning overlay
	auto lightingFilter = parent()->parentScene()->createGameObject("LIGHTNING_FOREGROUND_FILTER_1", -1.0F, -1.0F, 0.F, parent()->parentScene(), GameLayer::MAIN);
	houseMaskOverlayComponent->addOverlayObject(lightingFilter);

	
	m_stormComponenets.push_range(stormCompDistantBeginning);

}


void BBEnvironmentComponent::update()
{






	//m_stormComponenets.pop_back();



	if (testLightningTimer.hasMetTargetDuration()) {


		/////////////////////
		//TODO:Add a toggleState to the stateComponent!! MAYBE?
		//////////////////////////////////////
		const auto& lightningOverlay = parent()->parentScene()->getFirstGameObjectByName("lightningBackgroundFinal");
		if (lightningOverlay.value()->hasState(GameObjectState::DISABLED_RENDER)) {

			lightningOverlay.value()->removeState(GameObjectState::DISABLED_RENDER);

		}
		else {

			lightningOverlay.value()->addState(GameObjectState::DISABLED_RENDER);

		}



	}

	if (testLightningTimer2.hasMetTargetDuration()) {

		const auto& lightningOverlay = parent()->parentScene()->getFirstGameObjectByName("lightningBackground");
		if (lightningOverlay.value()->hasState(GameObjectState::DISABLED_RENDER)) {

			lightningOverlay.value()->removeState(GameObjectState::DISABLED_RENDER);

		}
		else {

			lightningOverlay.value()->addState(GameObjectState::DISABLED_RENDER);

		}

	}

	if (testLightningTimer3.hasMetTargetDuration()) {

		const auto& houseOverlayObject = parent()->parentScene()->getFirstGameObjectByType("HOUSE_OVERLAY");
		const auto& maskOverlayComponent = houseOverlayObject.value()->getComponent<MaskedOverlayComponent>(ComponentTypes::MASKED_OVERLAY_COMPONENT);
		auto lightningFilterObject = maskOverlayComponent->getOverlayObject("LIGHTNING_FOREGROUND_FILTER_1");

		if (lightningFilterObject.value()->hasState(GameObjectState::DISABLED_RENDER)) {

			lightningFilterObject.value()->removeState(GameObjectState::DISABLED_RENDER);

		}
		else {

			lightningFilterObject.value()->addState(GameObjectState::DISABLED_RENDER);

		}

	}



}

void BBEnvironmentComponent::setParent(GameObject* gameObject)
{
	//Call base component setParent
	Component::setParent(gameObject);

}


