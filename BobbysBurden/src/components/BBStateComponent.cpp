#include "BBStateComponent.h"
#include "../GameConstants.h"



BBStateComponent::BBStateComponent(Json::Value definitionJSON) : StateComponent(definitionJSON) 
{

}


void BBStateComponent::removeState(GameObjectState newState)
{

	if (testState(newState)) {

		switch (newState) {

			case GameObjectState::ON_VERTICAL_MOVEMENT:

				//Set the state to true
				m_states.set((int)newState, false);

				if (parent()->hasComponent(ComponentTypes::PHYSICS_COMPONENT) &&
					parent()->hasComponent(ComponentTypes::VITALITY_COMPONENT)) {

					const auto& playerPhysics = parent()->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);
					const auto& playerVitality = parent()->getComponent<VitalityComponent>(ComponentTypes::VITALITY_COMPONENT);

					playerPhysics->setGravityScale(15);
					playerPhysics->setLinearDamping(1);
					playerPhysics->setAngularDamping(1);
					playerVitality->setSpeed(3);
				}

			break;



		default: //If no match then call the base class

			StateComponent::removeState(newState);

		}


	}
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

		case GameObjectState::ON_VERTICAL_MOVEMENT:

			//Set the state to true
			m_states.set((int)newState, true);

			if (parent()->hasComponent(ComponentTypes::PHYSICS_COMPONENT) &&
				parent()->hasComponent(ComponentTypes::VITALITY_COMPONENT)) {

				const auto& playerPhysics = parent()->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);
				const auto& playerVitality = parent()->getComponent<VitalityComponent>(ComponentTypes::VITALITY_COMPONENT);

				playerPhysics->setGravityScale(0);
				playerPhysics->setLinearDamping(75);
				playerPhysics->setAngularDamping(100);
				playerVitality->setSpeed(5);
			}

			break;

	default: //If no match then call the base class

		StateComponent::addState(newState);

	}

}



