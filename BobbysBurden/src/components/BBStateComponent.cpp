#include "BBStateComponent.h"
#include "../GameConstants.h"



BBStateComponent::BBStateComponent(Json::Value definitionJSON) : StateComponent(definitionJSON) 
{

}

void BBStateComponent::addState(int newState)
{

	//Check to see if we have a transition defined for this state combination
	//Also, if the gameObject already has the state, dont try to set it again
	if (_checkTransition(newState) == false && testState(newState) == false) {


		_addState(newState);

		switch (newState) {

		case GameObjectState::ITEM_OBTAINABLE:

			m_states.set(GameObjectState::ITEM_STORED_PLAYER, false);
			break;

		case GameObjectState::ITEM_STORED_ENCLOSED:

			m_states.set(GameObjectState::ITEM_STORED_PLAYER, false);
			break;

		case GameObjectState::WALK_LEFT:

			m_states.set(GameObjectState::WALK_RIGHT, false);
			m_states.set(GameObjectState::WALK_UP, false);
			m_states.set(GameObjectState::WALK_DOWN, false);
			m_states.set(GameObjectState::IDLE_RIGHT, false);
			m_states.set(GameObjectState::IDLE_LEFT, false);
			m_states.set(GameObjectState::IDLE_UP, false);
			m_states.set(GameObjectState::IDLE_DOWN, false);
			break;

		case GameObjectState::WALK_RIGHT:

			m_states.set(GameObjectState::WALK_LEFT, false);
			m_states.set(GameObjectState::WALK_UP, false);
			m_states.set(GameObjectState::WALK_DOWN, false);
			m_states.set(GameObjectState::IDLE_RIGHT, false);
			m_states.set(GameObjectState::IDLE_LEFT, false);
			m_states.set(GameObjectState::IDLE_UP, false);
			m_states.set(GameObjectState::IDLE_DOWN, false);
			break;

		case GameObjectState::WALK_UP:

			m_states.set(GameObjectState::WALK_LEFT, false);
			m_states.set(GameObjectState::WALK_RIGHT, false);
			m_states.set(GameObjectState::WALK_DOWN, false);
			m_states.set(GameObjectState::IDLE_RIGHT, false);
			m_states.set(GameObjectState::IDLE_LEFT, false);
			m_states.set(GameObjectState::IDLE_UP, false);
			m_states.set(GameObjectState::IDLE_DOWN, false);
			break;

		case GameObjectState::WALK_DOWN:

			m_states.set(GameObjectState::WALK_LEFT, false);
			m_states.set(GameObjectState::WALK_RIGHT, false);
			m_states.set(GameObjectState::WALK_UP, false);
			m_states.set(GameObjectState::IDLE_RIGHT, false);
			m_states.set(GameObjectState::IDLE_LEFT, false);
			m_states.set(GameObjectState::IDLE_UP, false);
			m_states.set(GameObjectState::IDLE_DOWN, false);
			break;

		case GameObjectState::IDLE_RIGHT:

			m_states.set(GameObjectState::WALK_LEFT, false);
			m_states.set(GameObjectState::WALK_RIGHT, false);
			m_states.set(GameObjectState::WALK_UP, false);
			m_states.set(GameObjectState::WALK_DOWN, false);
			m_states.set(GameObjectState::IDLE_LEFT, false);
			m_states.set(GameObjectState::IDLE_UP, false);
			m_states.set(GameObjectState::IDLE_DOWN, false);
			break;

		case GameObjectState::IDLE_LEFT:

			m_states.set(GameObjectState::WALK_LEFT, false);
			m_states.set(GameObjectState::WALK_RIGHT, false);
			m_states.set(GameObjectState::WALK_UP, false);
			m_states.set(GameObjectState::WALK_DOWN, false);
			m_states.set(GameObjectState::IDLE_RIGHT, false);
			m_states.set(GameObjectState::IDLE_UP, false);
			m_states.set(GameObjectState::IDLE_DOWN, false);
			break;

		case GameObjectState::IDLE_UP:

			m_states.set(GameObjectState::WALK_LEFT, false);
			m_states.set(GameObjectState::WALK_RIGHT, false);
			m_states.set(GameObjectState::WALK_UP, false);
			m_states.set(GameObjectState::WALK_DOWN, false);
			m_states.set(GameObjectState::IDLE_RIGHT, false);
			m_states.set(GameObjectState::IDLE_LEFT, false);
			m_states.set(GameObjectState::IDLE_DOWN, false);
			break;

		case GameObjectState::IDLE_DOWN:

			m_states.set(GameObjectState::WALK_LEFT, false);
			m_states.set(GameObjectState::WALK_RIGHT, false);
			m_states.set(GameObjectState::WALK_UP, false);
			m_states.set(GameObjectState::WALK_DOWN, false);
			m_states.set(GameObjectState::IDLE_RIGHT, false);
			m_states.set(GameObjectState::IDLE_LEFT, false);
			m_states.set(GameObjectState::IDLE_UP, false);
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

			//If we have NOT started a transition timer then start one now
			if (transition.transitionTimer.has_value() == false) {

				transition.transitionTimer = Timer(transition.transitionDuration, false);

				//Tell animation component to animate the transition animation
				const auto& animationComponent = parent()->getComponent<AnimationComponent>(ComponentTypes::ANIMATION_COMPONENT);
				animationComponent->animate(transition.animationId);

				return true;

			}
			//If a transition timer was already started and its now expired, then clear it out
			else if(transition.transitionTimer.value().hasMetTargetDuration()) {

				transition.transitionTimer = std::nullopt;

				return false;

			}
			//The timer was started and its not finished
			else {

				return true;

			}

		}

	}


	return false;
}

