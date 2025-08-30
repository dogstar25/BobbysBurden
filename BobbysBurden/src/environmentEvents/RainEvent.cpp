#include "RainEvent.h"




RainEvent::RainEvent(std::variant<std::string, EventLevel, float> param, Timer durationTimer) :
	EnvironmentEvent(durationTimer)
{

	m_eventLevel = std::get<EventLevel>(param);

}


std::vector<std::shared_ptr<EnvironmentEvent>> RainEvent::perform(GameObject* environmentObject)
{

	///////////////////////////////
	//Test purposes - REMOVE
	return std::vector<std::shared_ptr<EnvironmentEvent>>();

	if (m_status == EventStatus::IDLE) {

		int randomNumber = std::rand() % 10;

		const auto& rainEmitter = environmentObject->parentScene()->getFirstGameObjectByType("PARTICLE_EMITTER_RAIN");
		if (rainEmitter.has_value()) {
			rainEmitter.value()->enableRender();
			rainEmitter.value()->enableUpdate();
			const auto& rainParticleComponent = rainEmitter.value()->getComponent<ParticleComponent>(ComponentTypes::PARTICLE_COMPONENT);

			switch (m_eventLevel) {

			case EventLevel::MILD:

				rainParticleComponent->setParticleEffectSpawnCount("RAIN", 20, 20);
				rainParticleComponent->setParticleEffectEmitAngle("RAIN", 88.0F, 92.0F);
				rainParticleComponent->setParticleEffectForce("RAIN", 40.0F, 50.0F);
				rainParticleComponent->setEmissionInterval(1.5f);

				break;
			case EventLevel::MODERATE:
				rainParticleComponent->setParticleEffectSpawnCount("RAIN", 20, 60);
				rainParticleComponent->setParticleEffectEmitAngle("RAIN", 41.0F, 48.0F);
				rainParticleComponent->setParticleEffectForce("RAIN", 50.0F, 70.0F);
				rainParticleComponent->setEmissionInterval(0.8f);

				break;
			case EventLevel::INTENSE:
				rainParticleComponent->setParticleEffectSpawnCount("RAIN", 40, 70);
				rainParticleComponent->setParticleEffectEmitAngle("RAIN", 40.0F, 50.0F);
				rainParticleComponent->setParticleEffectForce("RAIN", 60.0F, 80.0F);
				rainParticleComponent->setEmissionInterval(0.8f);

				break;
			default:
				break;

			}
		}

		m_durationTimer.reset();
		m_status = EventStatus::IN_PROGRESS;

	}

	return std::vector<std::shared_ptr<EnvironmentEvent>>();

}

void RainEvent::stop(GameObject* environmentObject)
{

	const auto& rainEmitter = environmentObject->parentScene()->getFirstGameObjectByType("PARTICLE_EMITTER_RAIN");
	rainEmitter.value()->disableRender();
	//rainEmitter.value()->disableUpdate();


}

