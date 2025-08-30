#include "BBStateComponent.h"
#include "../BBContextManager.h"
#include "../GameConstants.h"

extern std::unique_ptr<Game> game;

BBStateComponent::BBStateComponent(Json::Value definitionJSON, GameObject* parent) 
	: StateComponent(definitionJSON, parent)
{

}

void BBStateComponent::postInit()
{

	StateComponent::postInit();


	//Propogate the On/Off state
	if (testState(GameObjectState::ON) || testState(GameObjectState::OFF)) {

		Json::Value jsonArray(Json::arrayValue);
		Json::Value pair;

		if (testState(GameObjectState::ON)) {

			pair["forcedState"] = "GameObjectState::ON";
		}
		else if (testState(GameObjectState::OFF)) {

			pair["forcedState"] = "GameObjectState::OFF";
		}

		jsonArray.append(pair);
		std::shared_ptr<Action> onOffToggleAction = std::make_shared<OnOffToggleAction>(jsonArray, parent());
		onOffToggleAction->perform();

	}

}



void BBStateComponent::removeState(GameObjectState newState)
{

	if (testState(newState)) {

		switch (newState) {

			case GameObjectState::ON_VERTICAL_MOVEMENT:

				//Set the state to false
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

			case GameObjectState::ITEM_LOOSE:

				m_states.set((int)newState, false);

				//Restore to normal size
				parent()->revertToOriginalSize();

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

		case GameObjectState::ITEM_OBTAINABLE:

			m_states.set((int)newState, true);
			m_states.set((int)GameObjectState::ITEM_STORED_PLAYER, false);
			break;

		case GameObjectState::ITEM_STORED_ENCLOSED:

			m_states.set((int)newState, true);
			m_states.set((int)GameObjectState::ITEM_STORED_PLAYER, false);
			break;

		case GameObjectState::ITEM_STORED_OPEN:

			m_states.set((int)newState, true);
			m_states.set((int)GameObjectState::ITEM_STORED_ENCLOSED, false);
			m_states.set((int)GameObjectState::ITEM_STORED_PLAYER, false);
			break;

		case GameObjectState::ITEM_LOOSE:

			m_states.set((int)newState, true);
			m_states.set((int)GameObjectState::ITEM_STORED_PLAYER, false);
			m_states.set((int)GameObjectState::ITEM_STORED_ENCLOSED, false);

			//Set to world display size
			parent()->setSizeToWorldViewOverride();

			break;

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

void BBStateComponent::update()
{

	StateComponent::update();

}

//void BBStateComponent::_setOnOffStates()
//{
//
//	GameObjectState stateToPropogate{};
//
//	//Only deal with gameobjects that are set to off or on
//	if (testState(GameObjectState::ON)) {
//
//		stateToPropogate = GameObjectState::ON;
//	}
//	else if (testState(GameObjectState::OFF)) {
//
//		stateToPropogate = GameObjectState::OFF;
//	}
//	else {
//		return;
//	}
//
//	//First check if this switch works using named _TARGET
//	//If it does then apply state to the target object and all of its children that are tagged as toggleable
//
//	//If this is a toggle_switch, then we will propogate the state to the objects parent and all children underneath
//	if (parent()->hasTrait(TraitTag::toggle_switch)) {
//
//
//		std::string buttonTargetObjectName = parent()->name() + "_TARGET";
//		auto targetObjects = parent()->parentScene()->getGameObjectsByName(buttonTargetObjectName);
//		if (targetObjects.empty() == false) {
//
//
//			for (auto& targetObject : targetObjects) {
//
//
//				if (targetObject->hasTrait(TraitTag::toggleable)) {
//					targetObject->addState(stateToPropogate);
//				}
//				//turn off state of all children as well
//				propogateStateToAllChildren(targetObject.get(), stateToPropogate, TraitTag::toggleable);
//
//			}
//
//		}
//		else if (parent()->parent().has_value() &&
//			parent()->parent().value()->hasComponent(ComponentTypes::CHILDREN_COMPONENT)) {
//
//
//			if (parent()->parent().value()->hasTrait(TraitTag::toggleable)) {
//				parent()->parent().value()->addState(stateToPropogate);
//			}
//			propogateStateToAllChildren(parent()->parent().value(), stateToPropogate, TraitTag::toggleable);
//
//		}
//	}
//	//If this is a toggleable, then we will propogate the state to the children only
//	else if (parent()->hasTrait(TraitTag::toggleable)) {
//
//		propogateStateToAllChildren(parent(), stateToPropogate, TraitTag::toggleable);
//	}
//
//
//
//}


void BBStateComponent::flipBobby()
{

	if (testState(GameObjectState::IDLE_LEFT)) {
		addState(GameObjectState::IDLE_RIGHT);
	}
	else if (testState(GameObjectState::IDLE_LEFT_EQUIPPED)) {
		addState(GameObjectState::IDLE_RIGHT_EQUIPPED);
	}
	else if (testState(GameObjectState::WALK_LEFT)) {
		addState(GameObjectState::WALK_RIGHT);
	}
	else if (testState(GameObjectState::WALK_LEFT_EQUIPPED)) {
		addState(GameObjectState::WALK_RIGHT_EQUIPPED);
	}
	else if (testState(GameObjectState::IDLE_RIGHT)) {
		addState(GameObjectState::IDLE_LEFT);
	}
	else if (testState(GameObjectState::IDLE_RIGHT_EQUIPPED)) {
		addState(GameObjectState::IDLE_LEFT_EQUIPPED);
	}
	else if (testState(GameObjectState::WALK_RIGHT)) {
		addState(GameObjectState::WALK_LEFT);
	}
	else if (testState(GameObjectState::WALK_RIGHT_EQUIPPED)) {
		addState(GameObjectState::WALK_LEFT_EQUIPPED);
	}


}



