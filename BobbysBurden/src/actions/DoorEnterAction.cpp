#include "DoorEnterAction.h"
#include "DoorToggleAction.h"
#include "../components/BBStateComponent.h"

extern std::unique_ptr<Game> game;

void DoorEnterAction::perform(GameObject* doorEntryObject)
{

	const auto& player = doorEntryObject->parentScene()->getFirstGameObjectByTrait(TraitTag::player);
	perform(player->get(), doorEntryObject);

}


void DoorEnterAction::perform(GameObject* playerObject, GameObject* doorEntryObject)
{

	const auto& doorObject = doorEntryObject->parent();
	const auto& playerPhysicsComponent = playerObject->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);

	static Timer DisableEntryTimer{};


	if (DisableEntryTimer.hasMetTargetDuration() == false) {
		return;
	}

	std::optional<GameObject*> partnerDoor{};

	//Get this doors matching partner to sets its state as well
	//It's possible that a partner door does not exist
	const auto& doors = doorObject.value()->parentScene()->getGameObjectsByName(doorObject.value()->name());
	for (const auto& door : doors) {
		if (door.get() != doorObject) {

			partnerDoor = door.get();
			break;

		}
	}

	//Get the partner doors exit point
	if (partnerDoor.has_value()) {

		const auto& partnerDoorChildrenComponent = partnerDoor.value()->getComponent<ChildrenComponent>(ComponentTypes::CHILDREN_COMPONENT);
		const auto& exitPointObject = partnerDoorChildrenComponent->getFirstChildByType("DOOR_EXIT_POINT");


		//Warp the player to the exit point location
		if (exitPointObject.has_value()) {

			b2Vec2 destinationLocation = { exitPointObject.value()->getCenterPosition().x, exitPointObject.value()->getCenterPosition().y };
			util::toBox2dPoint(destinationLocation);
			playerPhysicsComponent->setTransform(destinationLocation);

		}

		//Disable the partner doors entry point for a second so that hitting the 'W' key doesnt warp the player back and forth
		//This is only a problem when both the origin door and partner exit door are front facing doors
		const auto& entryPointObject = partnerDoorChildrenComponent->getFirstChildByType("DOOR_FRONT_ENTRY_POINT");
		if (entryPointObject.has_value()) {

			DisableEntryTimer = Timer(1);

			//This is the front door to front door scenario so flip the player the oppositte direction
			const std::shared_ptr<BBStateComponent> playerStateComponent = dynamic_pointer_cast<BBStateComponent>(
				playerObject->getComponent<StateComponent>(ComponentTypes::STATE_COMPONENT));

			playerStateComponent->flipBobby();

		}


	}


}
