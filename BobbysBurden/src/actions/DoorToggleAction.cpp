#include "DoorToggleAction.h"
#include "../GameConstants.h"

extern std::unique_ptr<Game> game;

void DoorToggleAction::perform()
{

	const auto& doorObject = m_parent->parent().value();

	const auto& stateComponent = doorObject->getComponent<StateComponent>(ComponentTypes::STATE_COMPONENT);
	auto isOpen = stateComponent->testState(GameObjectState::OPENED);

	std::optional<GameObject*> partnerDoor{};

	//Get this doors matching partner to sets its state as well
	//It's possible that a partner door does not exist
	const auto& doors = doorObject->parentScene()->getGameObjectsByName(doorObject->name());
	for (const auto& door : doors) {
		if (door.get() != doorObject) {

			partnerDoor = door.get();
			break;

		}
	}

	//Set the state
	if (isOpen) {

		stateComponent->addState(GameObjectState::CLOSED);

		if (doorObject->hasTrait(TraitTag::door_side)) {
			doorObject->enableCollision();
			doorObject->addState(GameObjectState::IMPASSABLE);
		}
		if (partnerDoor.has_value()) {

			partnerDoor.value()->getComponent<StateComponent>(ComponentTypes::STATE_COMPONENT)->addState(GameObjectState::CLOSED);;

			//
			//todd: remove the disabled state
			//
			partnerDoor.value()->enableCollision();
		}

	}
	else {
		stateComponent->addState(GameObjectState::OPENED);

		if (doorObject->hasTrait(TraitTag::door_side)) {
			doorObject->disableCollision();
			doorObject->removeState(GameObjectState::IMPASSABLE);
		}

		//If there is a partner door, set state to opened and disabled its collision
		if (partnerDoor.has_value()) {

			partnerDoor.value()->getComponent<StateComponent>(ComponentTypes::STATE_COMPONENT)->addState(GameObjectState::OPENED);;
			partnerDoor.value()->disableCollision();
		}

	}



}

