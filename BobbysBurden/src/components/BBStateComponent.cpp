#include "BBStateComponent.h"



BBStateComponent::BBStateComponent(Json::Value definitionJSON) : StateComponent(definitionJSON) 
{

}

void BBStateComponent::initializeMutuallyExclusiveStates()
{
}

void BBStateComponent::setState(GameObjectState newState)
{

	//set the state
	State state;
	m_states.insert(state);

	switch (state.state) {

	case GameObjectState::ITEM_OBTAINABLE:

		m_states.erase({ GameObjectState::ITEM_STORED_PLAYER });
		break;

	case GameObjectState::ITEM_STORED_ENCLOSED:

		m_states.erase({ GameObjectState::ITEM_STORED_PLAYER });
		break;

		//If no match then call the base class
	default:

		StateComponent::setState(newState);

	}

}

