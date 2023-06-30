#include "BBInterfaceComponent.h"
#include "../GameConstants.h"


BBInterfaceComponent::BBInterfaceComponent(Json::Value definitionJSON, Scene* parentScene) :
	InterfaceComponent(definitionJSON, parentScene) {

}

void BBInterfaceComponent::setCursor(GameObject* gameObject, bool isMouseOver)
{

	//If the mouse is Over the object then set the cursor based on various factors
	if (isMouseOver) {

		//Door cursors
		if (gameObject->hasTrait(TraitTag::door)) {

			const auto& animationComponent =
				parent()->getComponent<AnimationComponent>(ComponentTypes::ANIMATION_COMPONENT);

			if (animationComponent->currentAnimationState() == AnimationState::OPENED) {

				auto cursor = TextureManager::instance().getMouseCursor("CURSOR_DOOR_CLOSE");
				SDL_SetCursor(cursor);
			}
			else {

				auto cursor = TextureManager::instance().getMouseCursor("CURSOR_DOOR_OPEN");
				SDL_SetCursor(cursor);
			}
		}
		else if (gameObject->hasTrait(TraitTag::puzzle)) {

			auto cursor = TextureManager::instance().getMouseCursor("CURSOR_HAND_POINT");
			SDL_SetCursor(cursor);


		}
	}
	else {

		auto cursor = TextureManager::instance().getMouseCursor("CURSOR_HAND_POINT");
		SDL_SetCursor(cursor);

	}




}

void BBInterfaceComponent::postInit() {


	InterfaceComponent::postInit();

	//The remoteLocationObject - we need to call this here to override what was dont in base postinit
	//because BB_INTERFACE_COMPONENT would not be found in the base definition
	GameObjectDefinition gameObjectDefinition = parent()->gameObjectDefinition();
	Json::Value componentDefinition = util::getComponentConfig(gameObjectDefinition.definitionJSON(), ComponentTypes::BB_INTERFACE_COMPONENT);
	if (componentDefinition.isMember("remoteLocationObject")) {

		std::string name = componentDefinition["remoteLocationObject"].asString();
		m_remoteLocationObject = parent()->parentScene()->getFirstGameObjectByName(name);

	}

}

