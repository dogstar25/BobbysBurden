#include "BobbyMoveAction.h"



//#include "GameObject.h"


void BobbyMoveAction::perform(GameObject* playerGameObject, int direction, int strafe)
{
	const auto& physicsComponent = playerGameObject->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);
	const auto& animationComponent = playerGameObject->getComponent<AnimationComponent>(ComponentTypes::ANIMATION_COMPONENT);
	const auto& stateComponent = playerGameObject->getComponent<StateComponent>(ComponentTypes::STATE_COMPONENT);
	const auto& vitalityComponent = playerGameObject->getComponent<VitalityComponent>(ComponentTypes::VITALITY_COMPONENT);

	physicsComponent->applyMovement(vitalityComponent->speed(), direction, strafe);

	//Get the entire before state so we can compare later to see if anything changed
	auto beforeState = stateComponent->getStateBitSet();

	if (direction != 0 || strafe != 0)
	{
		//If headed left or right, we use the walk right and left regardless

		if (strafe <  0) {

			if (stateComponent->testState(GameObjectState::EQUIPPED)) {
				stateComponent->addState(GameObjectState::WALK_LEFT_EQUIPPED);
			}
			else {
				stateComponent->addState(GameObjectState::WALK_LEFT);
			}
		}
		else if (strafe > 0) {

			if (stateComponent->testState(GameObjectState::EQUIPPED)) {
				stateComponent->addState(GameObjectState::WALK_RIGHT_EQUIPPED);
			}
			else {
				stateComponent->addState(GameObjectState::WALK_RIGHT);
			}
		}

		else {

			if (stateComponent->testState(GameObjectState::ON_VERTICAL_MOVEMENT)) {

				if (direction == -1) {

					if (stateComponent->testState(GameObjectState::EQUIPPED)) {
						stateComponent->addState(GameObjectState::WALK_UP_EQUIPPED);
					}
					else {
						stateComponent->addState(GameObjectState::WALK_UP);
					}
				}
				else {

					if (stateComponent->testState(GameObjectState::EQUIPPED)) {
						stateComponent->addState(GameObjectState::WALK_DOWN_EQUIPPED);
					}
					else {
						stateComponent->addState(GameObjectState::WALK_DOWN);
					}

				}
			}
			else{

				//handle entering door?
				if (direction == -1) {

					auto doorEntryObject = playerGameObject->getFirstTouchingByType("DOOR_FRONT_ENTRY_POINT");

					if (doorEntryObject.has_value()) {

						const auto& doorEntryContactObject = doorEntryObject.value().lock().get();
						const auto& doorObject = doorEntryContactObject->parent();
						const auto& doorStateComponent = doorObject.value()->getComponent<StateComponent>(ComponentTypes::STATE_COMPONENT);
						const auto& doorActionComponent = doorObject.value()->getComponent<ActionComponent>(ComponentTypes::ACTION_COMPONENT);

						//auto doorState = doorAnimationComponent->currentAnimationState();
						const auto& enterAction = doorActionComponent->getAction(Actions::ENTER);

						if (doorStateComponent->testState(GameObjectState::OPENED)) {

							enterAction->perform(playerGameObject, doorEntryObject.value().lock().get());
						}

					}

				}
			}

		}

	}
	//Set to Idle
	else {

			if (stateComponent->testState(GameObjectState::WALK_UP) || stateComponent->testState(GameObjectState::WALK_UP_EQUIPPED)) {

				if (stateComponent->testState(GameObjectState::EQUIPPED)) {
					stateComponent->addState(GameObjectState::IDLE_UP_EQUIPPED);
				}
				else {
					stateComponent->addState(GameObjectState::IDLE_UP);
				}
			}
			else if (stateComponent->testState(GameObjectState::WALK_DOWN) || stateComponent->testState(GameObjectState::WALK_DOWN_EQUIPPED)) {

				if (stateComponent->testState(GameObjectState::EQUIPPED)) {
					stateComponent->addState(GameObjectState::IDLE_DOWN_EQUIPPED);
				}
				else {
					stateComponent->addState(GameObjectState::IDLE_DOWN);
				}

			}

			else if (stateComponent->testState(GameObjectState::WALK_RIGHT) || stateComponent->testState(GameObjectState::WALK_RIGHT_EQUIPPED)) {

				if (stateComponent->testState(GameObjectState::EQUIPPED)) {
					stateComponent->addState(GameObjectState::IDLE_RIGHT_EQUIPPED);
				}
				else {
					stateComponent->addState(GameObjectState::IDLE_RIGHT);
				}
			}
			else if (stateComponent->testState(GameObjectState::WALK_LEFT) || stateComponent->testState(GameObjectState::WALK_LEFT_EQUIPPED)) {

				if (stateComponent->testState(GameObjectState::EQUIPPED)) {
					stateComponent->addState(GameObjectState::IDLE_LEFT_EQUIPPED);
				}
				else {
					stateComponent->addState(GameObjectState::IDLE_LEFT);
				}

			}
			else if (stateComponent->testState(GameObjectState::IDLE_LEFT) || stateComponent->testState(GameObjectState::IDLE_LEFT_EQUIPPED)) {

				if (stateComponent->testState(GameObjectState::EQUIPPED)) {
					stateComponent->addState(GameObjectState::IDLE_LEFT_EQUIPPED);
				}else{
					stateComponent->addState(GameObjectState::IDLE_LEFT);
				}

			}
			else if (stateComponent->testState(GameObjectState::IDLE_RIGHT) || stateComponent->testState(GameObjectState::IDLE_RIGHT_EQUIPPED)) {

				if (stateComponent->testState(GameObjectState::EQUIPPED)) {
					stateComponent->addState(GameObjectState::IDLE_RIGHT_EQUIPPED);
				}
				else {
					stateComponent->addState(GameObjectState::IDLE_RIGHT);
				}

			}
			else if (stateComponent->testState(GameObjectState::IDLE_UP) || stateComponent->testState(GameObjectState::IDLE_UP_EQUIPPED)) {

				if (stateComponent->testState(GameObjectState::EQUIPPED)) {
					stateComponent->addState(GameObjectState::IDLE_UP_EQUIPPED);
				}
				else {
					stateComponent->addState(GameObjectState::IDLE_UP);
				}

			}
			else if (stateComponent->testState(GameObjectState::IDLE_DOWN) || stateComponent->testState(GameObjectState::IDLE_DOWN_EQUIPPED)) {

				if (stateComponent->testState(GameObjectState::EQUIPPED)) {
					stateComponent->addState(GameObjectState::IDLE_DOWN_EQUIPPED);
				}
				else {
					stateComponent->addState(GameObjectState::IDLE_DOWN);
				}

			}

	}

	//We need to reposition the object that bobby is carrying if he has some equipped
	//only if the state changed
	auto afterState = stateComponent->getStateBitSet();
	if (stateComponent->testState(GameObjectState::EQUIPPED) && beforeState != afterState) {

		_repositionEquippedItem("HOLDING_CANDLE", playerGameObject);

	}

}


void BobbyMoveAction::_repositionEquippedItem(std::string gameObjectType, GameObject* bobbyObject)
{

	const auto& stateComponent = bobbyObject->getComponent<StateComponent>(ComponentTypes::STATE_COMPONENT);
	const auto& childrenComponent = bobbyObject->getComponent<ChildrenComponent>(ComponentTypes::CHILDREN_COMPONENT);

	if (stateComponent->testState(GameObjectState::WALK_RIGHT_EQUIPPED) ||
		stateComponent->testState(GameObjectState::IDLE_RIGHT_EQUIPPED)){

		childrenComponent->changeChildPosition(gameObjectType, { 38., -20. });

	}
	else if (stateComponent->testState(GameObjectState::WALK_LEFT_EQUIPPED) ||
		stateComponent->testState(GameObjectState::IDLE_LEFT_EQUIPPED)){

		childrenComponent->changeChildPosition(gameObjectType, { -38., -20. });

	}
	else if (stateComponent->testState(GameObjectState::WALK_UP_EQUIPPED) ||
		stateComponent->testState(GameObjectState::IDLE_UP_EQUIPPED)) {

		childrenComponent->changeChildPosition(gameObjectType, { 30., -12. });

	}
	else if (stateComponent->testState(GameObjectState::IDLE_DOWN_EQUIPPED) ||
		stateComponent->testState(GameObjectState::WALK_DOWN_EQUIPPED)) {

		childrenComponent->changeChildPosition(gameObjectType, { -8., 0. });

	}


}