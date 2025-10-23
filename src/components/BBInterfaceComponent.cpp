#include "BBInterfaceComponent.h"
#include "../GameConstants.h"

//extern std::unique_ptr<Game> game;


BBInterfaceComponent::BBInterfaceComponent(Json::Value componentJSON, GameObject* parent, Scene* parentScene) :
	InterfaceComponent(componentJSON, parent, parentScene)
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

		if (m_currentGameObjectInterfaceActive.value() != parent() &&
			parent()->type() == "DOOR_SIDE_ENTRY_POINT") {

			hasHigherPriority = true;
		}

		if (m_currentGameObjectInterfaceActive.value() != parent() &&
			parent()->type() == "SCARY_OBJECT") {

			hasHigherPriority = true;
		}

		//Scenario where we are standing on the stairs area but we need the door to be available that is next to the stairs
		if (parent()->type() == "DOOR_KNOB" &&
			m_currentGameObjectInterfaceActive.value()->hasTrait(TraitTag::vertical_movement_zone)) {

			hasHigherPriority = true;

		}

		//Scenario where we want the skull holding the small key override the key interface itself
		if (parent()->type() == "SKULL" &&
			m_currentGameObjectInterfaceActive.value()->type() == "SMALL_KEY"){

			hasHigherPriority = true;

		}

	}

	return hasHigherPriority;
}

std::optional<std::shared_ptr<GameObject>> BBInterfaceComponent::determineItemContactInterfaceTarget(GameObject* itemObject)
{

	std::optional<std::shared_ptr<GameObject>> finalObject{};

	if (itemObject->getTouchingObjects().empty() == false) {

		const auto& player = itemObject->parentScene()->player();

		auto itemContactItr = itemObject->getTouchingObjects().begin()->second;

		//const auto& itemContactItr = itemObject->getTouchingObjects().begin();
		for (auto itemContactItr = itemObject->getTouchingObjects().begin();
			itemContactItr != itemObject->getTouchingObjects().end(); ++itemContactItr) {

			const auto candidateObject = itemContactItr->second;
			if (itemContactItr->second.expired() == false) {

				if (candidateObject.lock()->hasTrait(TraitTag::puzzle) || candidateObject.lock()->hasTrait(TraitTag::inventory))
				{

					//If if this is a normal inventory object or puzzle then the player has to be close enough touching it
					//but if its an inventory display object then player doesnt have to be touching it
					if (candidateObject.lock()->hasTrait(TraitTag::inventory_display) == true ||
						player->isTouchingById(candidateObject.lock()->id())) {

						//Initialize the first one
						if (!finalObject) {

							finalObject = candidateObject.lock();
							continue;
						}

						//If this item is on a higfher layer then it wins
						if (candidateObject.lock()->layer() > finalObject.value()->layer()) {

							finalObject = candidateObject.lock();
						}
					}

				}
			}

		}
	}

	return finalObject;

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

