#include "ToggleBobbyEquipAction.h"
#include "../GameConstants.h"

extern std::unique_ptr<Game> game;

void ToggleBobbyEquipAction::perform()
{

	if (m_parent->hasState(GameObjectState::EQUIPPED)) {

		m_parent->removeState(GameObjectState::EQUIPPED);
		_disableCandle(m_parent);

	}
	else {

		m_parent->addState(GameObjectState::EQUIPPED);
		_enableCandle(m_parent);

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

