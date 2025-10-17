#include "LightningEvent.h"




LightningEvent::LightningEvent(std::variant<std::string, EventLevel, float> param, Timer durationTimer) :
	EnvironmentEvent(durationTimer)
{

	m_eventLevel = std::get<EventLevel>(param);

}


std::vector<std::shared_ptr<EnvironmentEvent>> LightningEvent::perform(GameObject* environmentObject)
{

	

	//Show Lighting Flash
	if (m_status == EventStatus::IDLE) {

		int randomNumber = std::rand() % 10;

		if (m_eventLevel == EventLevel::MILD) {

			m_layer = LightningLayor::BACK;

		}
		else if (m_eventLevel == EventLevel::MODERATE) {

			if (randomNumber <= 4) {

				m_layer = LightningLayor::BACK;

			}
			//else {
			//	m_layer = LightningLayor::MIDDLE;
			//}

		}
		else if (m_eventLevel == EventLevel::INTENSE) {

			if (randomNumber <= 4) {

				m_layer = LightningLayor::BACK;

			}
			//else if (randomNumber <= 9) {
			//	m_layer = LightningLayor::MIDDLE;
			//}
			//else {
			//	m_layer = LightningLayor::FRONT;
			//}

		}

		//test
		//m_layer = LightningLayor::BACK;
		//////////

		if (m_layer == LightningLayor::BACK) {

			m_lightningOverlay = environmentObject->parentScene()->getFirstGameObjectByName("lightningBackgroundFinal");

		}
		else if (m_layer == LightningLayor::MIDDLE) {

			m_lightningOverlay = environmentObject->parentScene()->getFirstGameObjectByName("lightningBackground");

		}
		m_lightningOverlay.value()->removeState(GameObjectState::DISABLED_RENDER);
		m_status = EventStatus::IN_PROGRESS;

		m_durationTimer.reset();

	}

	//empty
	return std::vector<std::shared_ptr<EnvironmentEvent>>();

}

void LightningEvent::stop(GameObject* environmentObject)
{

	//Hide lighting flash
	if (m_durationTimer.hasMetTargetDuration()) {

		if (m_lightningOverlay.has_value()) {
			m_lightningOverlay.value()->addState(GameObjectState::DISABLED_RENDER);
		}
		m_status = EventStatus::COMPLETE;

	}

}

