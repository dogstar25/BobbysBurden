#include "ScareBobbyAction.h"
#include "../components/BBStateComponent.h"
#include "../GameConstants.h"

void ScareBobbyAction::perform(GameObject* scaryObject)
{
	std::string scareType{"removeScare"};

	const auto& bobby = scaryObject->parentScene()->getFirstGameObjectByTrait(TraitTag::player);
	const auto& childrenComponent = bobby.value()->getComponent<ChildrenComponent>(ComponentTypes::CHILDREN_COMPONENT);
	const auto& playerController = bobby.value()->getComponent<PlayerControlComponent>(ComponentTypes::PLAYER_CONTROL_COMPONENT);
	const auto& stateComponent = bobby.value()->getComponent<BBStateComponent>(ComponentTypes::STATE_COMPONENT);
	const auto& physicsComponent = bobby.value()->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);

	const auto& nopeBubble = childrenComponent->getFirstChildByType("NOPE_BUBBLE");

	scareType = getActionProperty("parm").asString();

	if (scareType == "applyScare" && bobby.value()->hasState(GameObjectState::SCARED) == false) {

		bobby.value()->addState(GameObjectState::SCARED);

		nopeBubble.value()->enableRender();

		stateComponent->flipBobby();

	}
	else if (scareType == "removeScare") {

		bobby.value()->removeState(GameObjectState::SCARED);
		nopeBubble.value()->disableRender();

	}

}

