#include "ToggleBobbyEquipAction.h"
#include "../GameConstants.h"

extern std::unique_ptr<Game> game;

void ToggleBobbyEquipAction::perform(GameObject* playerObject)
{

	if (playerObject->hasState(GameObjectState::EQUIPPED)) {

		playerObject->removeState(GameObjectState::EQUIPPED);
		_disableCandle(playerObject);

	}
	else {

		playerObject->addState(GameObjectState::EQUIPPED);
		_enableCandle(playerObject);

	}


}

void ToggleBobbyEquipAction::_disableCandle(GameObject* gameObject)
{
	const auto& childrenComponent = gameObject->getComponent<ChildrenComponent>(ComponentTypes::CHILDREN_COMPONENT);
	const auto& candle = childrenComponent->getFirstChildByType("HOLDING_CANDLE");

	candle.value()->disableRender();
	candle.value()->addState(GameObjectState::OFF);
	StateComponent::propogateStateToAllChildren(candle.value().get(), GameObjectState::OFF);

}

void ToggleBobbyEquipAction::_enableCandle(GameObject* gameObject)
{

	const auto& stateComponent = gameObject->getComponent<StateComponent>(ComponentTypes::STATE_COMPONENT);
	const auto& childrenComponent = gameObject->getComponent<ChildrenComponent>(ComponentTypes::CHILDREN_COMPONENT);
	const auto& candle = childrenComponent->getFirstChildByType("HOLDING_CANDLE");

	candle.value()->enableRender();
	candle.value()->addState(GameObjectState::ON);
	StateComponent::propogateStateToAllChildren(candle.value().get(), GameObjectState::ON);



}

