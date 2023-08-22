#include "ItemDropAction.h"

extern std::unique_ptr<Game> game;

void ItemDropAction::perform(GameObject* gameObject)
{



	//If there was a overlay added to the dragging somewhere then make sure its clear
	const auto& renderComponent = gameObject->getComponent<RenderComponent>(ComponentTypes::RENDER_COMPONENT);
	renderComponent->removeDisplayOverlay();



}
