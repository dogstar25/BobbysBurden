#include "ActorMoveAction.h"



//#include "GameObject.h"


void ActorMoveAction::perform(GameObject* gameObject, int direction, int strafe)
{
	const auto& physicsComponent = gameObject->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);
	const auto& animationComponent = gameObject->getComponent<AnimationComponent>(ComponentTypes::ANIMATION_COMPONENT);
	const auto& stateComponent = gameObject->getComponent<StateComponent>(ComponentTypes::STATE_COMPONENT);
	const auto& vitalityComponent = gameObject->getComponent<VitalityComponent>(ComponentTypes::VITALITY_COMPONENT);

	if (strafe != 0 || direction == -1) {
		//physicsComponent->applyImpulse(vitalityComponent->speed(), direction, strafe);
		physicsComponent->applyMovement(vitalityComponent->speed(), direction, strafe);
	}


	if (animationComponent)
	{

		if (direction != 0 || strafe != 0)
		{
			if (strafe < 0) {

				stateComponent->addState(GameObjectState::WALK_LEFT);
				std::cout << "Set Left State" << std::endl;

			}
			else {
				stateComponent->addState(GameObjectState::WALK_RIGHT);
			}
		}
		//Set to Idle
		else {

			if (stateComponent->testState(GameObjectState::WALK_RIGHT)) {
				stateComponent->addState(GameObjectState::IDLE_RIGHT);
			}
			else if (stateComponent->testState(GameObjectState::WALK_LEFT)) {
				stateComponent->addState(GameObjectState::IDLE_LEFT);
			}

		}

	}

}