#include "SpiderDeployAction.h"
#include "../GameConstants.h"

void SpiderDeployAction::perform()
{

	const auto& stateComponent = m_parent->getComponent<StateComponent>(ComponentTypes::STATE_COMPONENT);

	std::string actionType = getActionProperty("actionType").asString();

	if (actionType == "UNDEPLOY") {

		stateComponent->addState(GameObjectState::IDLE);
		stateComponent->removeState(GameObjectState::DISABLED_COLLISION);

	}
	else if (actionType == "DEPLOY") {

		stateComponent->addState(GameObjectState::DEPLOYED);
		stateComponent->addState(GameObjectState::DISABLED_COLLISION);
	}

}

