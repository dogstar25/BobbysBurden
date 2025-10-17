#include "ScareBobbyAction.h"
#include "../components/BBStateComponent.h"
#include "../GameConstants.h"

void ScareBobbyAction::perform()
{
	std::string scareType{"removeScare"};

	const auto& bobby = m_parent->parentScene()->player();
	const auto& childrenComponent = bobby->getComponent<ChildrenComponent>(ComponentTypes::CHILDREN_COMPONENT);
	const auto& playerController = bobby->getComponent<PlayerControlComponent>(ComponentTypes::PLAYER_CONTROL_COMPONENT);
	const auto& stateComponent = bobby->getComponent<BBStateComponent>(ComponentTypes::STATE_COMPONENT);
	const auto& physicsComponent = bobby->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);

	const auto& nopeBubble = childrenComponent->getFirstChildByType("NOPE_BUBBLE");

	scareType = getActionProperty("parm").asString();

	if (scareType == "applyScare" && bobby->hasState(GameObjectState::SCARED) == false) {

		bobby->addState(GameObjectState::SCARED);

		nopeBubble.value()->enableRender();

		stateComponent->flipBobby();

	}
	else if (scareType == "removeScare") {

		bobby->removeState(GameObjectState::SCARED);
		nopeBubble.value()->disableRender();

	}

}

