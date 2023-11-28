#include "BBStateComponent.h"
#include "../GameConstants.h"



BBStateComponent::BBStateComponent(Json::Value definitionJSON) : StateComponent(definitionJSON) 
{

}

void BBStateComponent::addState(int newState)
{

	//Check to see if we have a transition defined for this state combination
	if (_checkTransition(newState) == false) {


		m_states.set(newState, true);

		switch (newState) {

		case GameObjectState::ITEM_OBTAINABLE:

			m_states.set(GameObjectState::ITEM_STORED_PLAYER, false);
			break;

		case GameObjectState::ITEM_STORED_ENCLOSED:

			m_states.set(GameObjectState::ITEM_STORED_PLAYER, false);
			break;

		default: //If no match then call the base class

			StateComponent::addState(newState);

		}
	}

}

bool BBStateComponent::_checkTransition(int newState)
{

	for (auto transition : m_transitions) {

		//If we have a transition defined that matches the states that we are trying to go to and from
		if (m_states.test(transition.fromState) == true && transition.toState == newState) {

			//Have we already started a transition timer for it and if so, has it expired
			if (transition.transitionTimer.has_value() == false) {

				transition.transitionTimer = Timer(transition.transitionDuration, false);

			}


		}

	}


	return false;
}

