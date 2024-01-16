#include "ActorMoveAction.h"



//#include "GameObject.h"


void ActorMoveAction::perform(GameObject* playerGameObject, int direction, int strafe)
{
	const auto& physicsComponent = playerGameObject->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);
	const auto& animationComponent = playerGameObject->getComponent<AnimationComponent>(ComponentTypes::ANIMATION_COMPONENT);
	const auto& stateComponent = playerGameObject->getComponent<StateComponent>(ComponentTypes::STATE_COMPONENT);
	const auto& vitalityComponent = playerGameObject->getComponent<VitalityComponent>(ComponentTypes::VITALITY_COMPONENT);

	//if (strafe != 0 || direction == -1) {

		physicsComponent->applyMovement(vitalityComponent->speed(), direction, strafe);
	//}

	if (direction != 0 || strafe != 0)
	{
		//If headed left or right, we use the walk right and left regardless

		if (strafe <  0) {

			stateComponent->addState(GameObjectState::WALK_LEFT);
		}
		else if (strafe > 0) {

			stateComponent->addState(GameObjectState::WALK_RIGHT);
		}

		else {

			if (stateComponent->testState(GameObjectState::ON_VERTICAL_MOVEMENT)) {

				if (direction == -1) {

					stateComponent->addState(GameObjectState::WALK_UP);
				}
				else {

					stateComponent->addState(GameObjectState::WALK_DOWN);

				}
			}
			else{

				//handle entering door?
				if (direction == -1) {

					auto doorEntryContact = playerGameObject->getFirstTouchingByTrait(TraitTag::door_entry);

					if (doorEntryContact.has_value()) {

						const auto& doorEntryContactObject = doorEntryContact.value().lock().get();
						const auto& doorObject = doorEntryContactObject->parent();
						const auto& doorStateComponent = doorObject.value()->getComponent<StateComponent>(ComponentTypes::STATE_COMPONENT);
						const auto& doorActionComponent = doorObject.value()->getComponent<ActionComponent>(ComponentTypes::ACTION_COMPONENT);

						//auto doorState = doorAnimationComponent->currentAnimationState();
						const auto& enterAction = doorActionComponent->getAction(Actions::ENTER);

						if (doorStateComponent->testState(GameObjectState::OPENED)) {

							enterAction->perform(playerGameObject, doorObject.value());
						}

					}

				}
			}

		}

	}
	//Set to Idle
	else {

			if (stateComponent->testState(GameObjectState::WALK_UP)) {

				stateComponent->addState(GameObjectState::IDLE_UP);
			}
			else if (stateComponent->testState(GameObjectState::WALK_DOWN)) {

				stateComponent->addState(GameObjectState::IDLE_DOWN);

			}

			else if (stateComponent->testState(GameObjectState::WALK_RIGHT)) {

				stateComponent->addState(GameObjectState::IDLE_RIGHT);
			}
			else if (stateComponent->testState(GameObjectState::WALK_LEFT)) {

				stateComponent->addState(GameObjectState::IDLE_LEFT);
			}

	}


}