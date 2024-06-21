#include "BBInterfaceComponent.h"
#include "../GameConstants.h"

extern std::unique_ptr<Game> game;


BBInterfaceComponent::BBInterfaceComponent(Json::Value componentJSON, Scene* parentScene) :
	InterfaceComponent(componentJSON, parentScene)
{

	//For all interface events that were already built in the base classes construtor
	//go and find any dependent puzzle items that are tied to this event
	for (Json::Value itr : componentJSON["interfaceActions"]) {

		int actionId = game->enumMap()->toEnum(itr["actionId"].asString());

		if (itr.isMember("dependentPuzzles")) {
			for (Json::Value puzzleItr : itr["dependentPuzzles"]) {

				m_dependentPuzzles[actionId] = puzzleItr.asString();

			}
		}

	}

}

bool BBInterfaceComponent::isEventAvailable(int actionId)
{
	bool isAvailable{};

	//Do we have a puzzle component that could make this event NOT available?
	if (m_dependentPuzzles.find(actionId) != m_dependentPuzzles.end()) {

		const auto& puzzleComponent = parent()->getComponent<PuzzleComponent>(ComponentTypes::PUZZLE_COMPONENT);
		if (puzzleComponent->hasBeenSolved() == true) {
			isAvailable =  true;
		}

	}
	else {

		isAvailable = true;
	}

	return isAvailable;
}


//Remember that this is from the perspective of the game object whose interface we are deciding 
//should display instead of the interfaces object current stored in m_currentGameObjectInterfaceActive
bool BBInterfaceComponent::doesInterfaceHavePriority(std::bitset<MAX_EVENT_STATES> eventState)
{
	bool hasHigherPriority{true};

	if (m_currentGameObjectInterfaceActive.has_value()) {

		hasHigherPriority = false;

		if (m_currentGameObjectInterfaceActive.value() == parent()) {

			hasHigherPriority = true;
		}

		if (parent()->hasTrait(TraitTag::player)) {

			hasHigherPriority = true;
		}

		if (m_currentGameObjectInterfaceActive.value()->renderOrder() < parent()->renderOrder() &&
			m_currentGameObjectInterfaceActive.value()->isDragging() == false) {

			hasHigherPriority = true;
		}

		//Certain events should always have priority, like dropping an object or stop tpuching
		if (eventState.test((int)InterfaceEvents::ON_DROP) ||
			eventState.test((int)InterfaceEvents::ON_DRAG) ||
			eventState.test((int)InterfaceEvents::ON_STOP_TOUCHING) ) {

			hasHigherPriority = true;

		}

		if (m_currentGameObjectInterfaceActive.value() != parent() &&
			m_currentGameObjectInterfaceActive.value()->type() == "PUZZLE_HINT_SENSOR_BOX"){

			hasHigherPriority = true;
		}

		//Scenario where we are standing on the stairs area but we need the door to be available that is next to the stairs
		if (parent()->type() == "DOOR_KNOB" &&
			m_currentGameObjectInterfaceActive.value()->hasTrait(TraitTag::vertical_movement_zone)) {

			hasHigherPriority = true;

		}


	}

	return hasHigherPriority;
}

//bool BBInterfaceComponent::shouldInterfaceMenuBeShown(std::bitset<(int)InterfaceEvents::COUNT> eventState)
//{
//
//	//At this point, we know the interface(with or without a menu will be active)
//	// This is only applicable to the action "Actions::ShowInterface"
//	//showing menu precedence
//	//	If this is showing in the main hud, then 
//
//
//	return true;
//}


void BBInterfaceComponent::postInit() {


}

bool BBInterfaceComponent::isDraggingAllowed()
{

	if (parent()->hasState(GameObjectState::ITEM_LOOSE) && parent()->isTouchingByTrait(TraitTag::player) == false) {

		return false;
	}


	return true;
}

void BBInterfaceComponent::render()
{

	InterfaceComponent::render();

}

