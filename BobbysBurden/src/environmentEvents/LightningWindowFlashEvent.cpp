#include "LightningWindowFlashEvent.h"




LightningWindowFlashEvent::LightningWindowFlashEvent(std::variant<std::string, EventLevel, float> param, Timer durationTimer) :
	EnvironmentEvent(durationTimer)
{

	m_eventLevel = std::get<EventLevel>(param);

}


std::vector<std::shared_ptr<EnvironmentEvent>> LightningWindowFlashEvent::perform(GameObject* environmentObject)
{

	//Show Lighting Flash
	if (m_status == EventStatus::IDLE) {

		m_status = EventStatus::IN_PROGRESS;
		_flipWindowFlash(environmentObject, GameObjectState::ON);
		m_durationTimer.reset();

	}

	return std::vector<std::shared_ptr<EnvironmentEvent>>();

}

void LightningWindowFlashEvent::_flipWindowFlash(GameObject* environmentObject, GameObjectState newState)
{

	const auto& windowFlashObjects = environmentObject->parentScene()->getGameObjectsByName("windowFlash");

	for (const auto& windowFlash : windowFlashObjects) {

		const auto& stateComponent = windowFlash->getComponent<StateComponent>(ComponentTypes::STATE_COMPONENT);
		stateComponent->addState(newState);

	}


}


void LightningWindowFlashEvent::stop(GameObject* environmentObject)
{

	//Hide lighting flash
	_flipWindowFlash(environmentObject, GameObjectState::OFF);

}

