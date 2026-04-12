#include "GhostDoorEnterAction.h"
#include "DoorToggleAction.h"
#include "../components/BBStateComponent.h"

//extern std::unique_ptr<Game> game;

void GhostDoorEnterAction::perform()
{

	const auto& doorObject = m_parent->parent();
	const auto ghost = m_parent->parentScene()->getFirstGameObjectByType("GHOST");

	const auto& playerPhysicsComponent = ghost.value()->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);

	std::optional<GameObject*> partnerDoor{};

	//Get this doors matching partner
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


		//Warp the ghost to the exit point location
		if (exitPointObject.has_value()) {

			b2Vec2 destinationLocation = { exitPointObject.value()->getCenterPosition().x, exitPointObject.value()->getCenterPosition().y };
			util::toBox2dPoint(destinationLocation);
			playerPhysicsComponent->setTransform(destinationLocation);

		}

	}


}
