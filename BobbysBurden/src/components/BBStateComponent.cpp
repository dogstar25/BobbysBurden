#include "BBStateComponent.h"
#include "../GameConstants.h"



BBStateComponent::BBStateComponent(Json::Value definitionJSON) : StateComponent(definitionJSON) 
{

}

void BBStateComponent::addState(GameObjectState newState)
{

	//Check to see if we have a transition defined for this state combination
	//Also, if the gameObject already has the state, dont try to set it again
	if (_hasTransitionDuration(newState) == false && testState(newState) == false) {

		_setAndReconcileState(newState);

	}

}

void BBStateComponent::_setAndReconcileState(GameObjectState newState)
{

	switch (newState) {
		//This can be used for overriding state rules

	default: //If no match then call the base class

		StateComponent::addState(newState);

	}

}



