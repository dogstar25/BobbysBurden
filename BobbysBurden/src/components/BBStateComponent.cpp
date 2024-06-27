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

	////Apply the On/OFF state of this object to all of its children
	//GameObjectState stateToPropogate{};
	//if (testState(GameObjectState::ON)) {

	//	util::propogateStateToAllChildren(parent(), GameObjectState::ON);
	//}
	//else if (testState(GameObjectState::OFF)) {

	//	util::propogateStateToAllChildren(parent(), GameObjectState::OFF);
	//}

	////If this is a toggle switch object then go through and apply the switches state to the objects that it controls
	//if (parent()->hasTrait(TraitTag::light_switch)) {

	//	std::shared_ptr<Action> onOffToggleAction = std::make_shared<OnOffLightToggleAction>();
	//	onOffToggleAction->perform(parent());

	//}



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

void BBStateComponent::update()
{

	StateComponent::update();

	//If this is the player object then set the special house location context variable
	//Is the player in the Back half or front half of the house
	if (parent()->hasTrait(TraitTag::player)) {

		_setHouseLocationContext();

	}

	if (parent()->hasTrait(TraitTag::toggle_switch)) {

		_setOnOffStates();

	}


}

void BBStateComponent::_setHouseLocationContext()
{

	if (parent()->getCenterPosition().y > 3520) {


		dynamic_pointer_cast<BBContextManager>(game->contextMananger())->setCurrentHousePosition(HousePositionTopLeftLocations::FRONT);

	}
	else {

		dynamic_pointer_cast<BBContextManager>(game->contextMananger())->setCurrentHousePosition(HousePositionTopLeftLocations::BACK);

	}


}


void BBStateComponent::_setOnOffStates()
{

	GameObjectState stateToPropogate{};

	//Only deal with gameobjects that are set to off or on
	if (testState(GameObjectState::ON)) {

		stateToPropogate = GameObjectState::ON;
	}
	else if (testState(GameObjectState::OFF)) {

		stateToPropogate = GameObjectState::OFF;
	}
	else {
		return;
	}

	//First check if this switch works using named _TARGET
	std::string buttonTargetObjectName = parent()->name() + "_TARGET";
	auto targetObjects = parent()->parentScene()->getGameObjectsByName(buttonTargetObjectName);
	if (targetObjects.empty() == false) {

		for (auto& targetObject : targetObjects) {

			targetObject->addState(stateToPropogate);
			//turn off state of all children as well
			util::propogateStateToAllChildren(targetObject.get(), stateToPropogate);

		}

	}
	else {

		if (parent()->parent().has_value() &&
			parent()->parent().value()->hasComponent(ComponentTypes::CHILDREN_COMPONENT)) {

			parent()->parent().value()->addState(stateToPropogate);
			util::propogateStateToAllChildren(parent()->parent().value(), stateToPropogate);

		}

	}


}


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



