#include "ActorStairsMoveAction.h"
#include "../GameConstants.h"

void ActorStairsMoveAction::perform(GameObject* gameObject, int direction)
{
	const auto& physicsComponent = gameObject->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);
	const auto& stateComponent = gameObject->getComponent<StateComponent>(ComponentTypes::STATE_COMPONENT);

	const auto& animationComponent = gameObject->getComponent<AnimationComponent>(ComponentTypes::ANIMATION_COMPONENT);
	const auto& vitalityComponent = gameObject->getComponent<VitalityComponent>(ComponentTypes::VITALITY_COMPONENT);

	if (direction == -1) {
		physicsComponent->applyMovement(vitalityComponent->speed(), direction, 0);
	}
	else {
		physicsComponent->applyMovement(vitalityComponent->speed(), direction, 0);
	}

	if (animationComponent)
	{

		if (direction == -1)
		{
			stateComponent->addState(GameObjectState::WALK_UP);
		}
		else if (direction == 1){

			stateComponent->addState(GameObjectState::WALK_DOWN);
		}
		else {

			if (stateComponent->testState(GameObjectState::WALK_UP)) {

				stateComponent->addState(GameObjectState::IDLE_UP);
			}
			else if (stateComponent->testState(GameObjectState::WALK_DOWN)) {

				stateComponent->addState(GameObjectState::IDLE_DOWN);
			}
		}

	}

}