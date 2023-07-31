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


void BBInterfaceComponent::setCursor(GameObject* gameObject, std::bitset<(int)InterfaceEvents::COUNT> eventState)
{

	//If the mouse is Over the object then set the cursor based on various factors
	//if (m_eventActions.find(Actions::USE) != m_eventActions.end()) {

	//	auto actionEvent = m_eventActions[Actions::USE];
	//	if (hasActionMetEventRequirements(actionEvent.get(), eventState)) {


	//		//Door
	//		if(gameObject->hasTrait())



	//	}

	//}
	
	//	//Door cursors
	//	if (gameObject->hasTrait(TraitTag::door)) {

	//		const auto& animationComponent =
	//			parent()->getComponent<AnimationComponent>(ComponentTypes::ANIMATION_COMPONENT);

	//		if (animationComponent->currentAnimationState() == AnimationState::OPENED) {

	//			auto cursor = TextureManager::instance().getMouseCursor("CURSOR_DOOR_CLOSE");
	//			SDL_SetCursor(cursor);
	//		}
	//		else {

	//			auto cursor = TextureManager::instance().getMouseCursor("CURSOR_DOOR_OPEN");
	//			SDL_SetCursor(cursor);
	//		}
	//	}
	//	else if (gameObject->hasTrait(TraitTag::puzzle)) {

	//		auto cursor = TextureManager::instance().getMouseCursor("CURSOR_HAND_POINT");
	//		SDL_SetCursor(cursor);


	//	}
	//}
	//else {

	//	auto cursor = TextureManager::instance().getMouseCursor("CURSOR_HAND_POINT");
	//	SDL_SetCursor(cursor);

	//}




}


bool BBInterfaceComponent::doesInterfaceHavePriority(std::bitset<(int)InterfaceEvents::COUNT> eventState)
{
	bool activate{true};

	if (m_currentGameObjectInterfaceActive.has_value()) {

		if (m_currentGameObjectInterfaceActive.value() == parent()) {

			activate = true;
		}
		//Is my Layer in front of the other object
		else if (m_currentGameObjectInterfaceActive.value()->layer() < parent()->layer()) {
			activate = true;
		}
		else {
			activate = false;
		}

	}

	return activate;
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


	//InterfaceComponent::postInit();

	////The remoteLocationObject - we need to call this here to override what was dont in base postinit
	////because BB_INTERFACE_COMPONENT would not be found in the base definition
	//GameObjectDefinition gameObjectDefinition = parent()->gameObjectDefinition();
	//Json::Value componentDefinition = util::getComponentConfig(gameObjectDefinition.definitionJSON(), ComponentTypes::BB_INTERFACE_COMPONENT);
	//if (componentDefinition.isMember("remoteLocationObject")) {

	//	std::string name = componentDefinition["remoteLocationObject"].asString();
	//	m_remoteLocationObject = parent()->parentScene()->getFirstGameObjectByName(name);

	//}

}

void BBInterfaceComponent::handleDragging()
{

	InterfaceComponent::handleDragging();

	// Move this to BBInterface
	//If the object being dragged is out of Bobby's reach range, then apply a red overlay
	if (parent()->isTouchingByTrait(TraitTag::player) == false) {

		const auto& renderComponent = parent()->getComponent<RenderComponent>(ComponentTypes::RENDER_COMPONENT);
		renderComponent->applyDisplayOverlay(displayOverlays::tint_RED1);
	}
	else {
		const auto& renderComponent = parent()->getComponent<RenderComponent>(ComponentTypes::RENDER_COMPONENT);
		renderComponent->removeDisplayOverlay();

	}

}

void BBInterfaceComponent::render()
{

	InterfaceComponent::render();

	//set the current interface global to be this one
	//m_currentGameObjectInterfaceActive = parent();

}

