#include "HideInterfaceAction.h"
#include "../components/BBInterfaceComponent.h"


void HideInterfaceAction::perform(GameObject* parentObject)
{

	const auto& interfaceComponent = parentObject->getComponent<BBInterfaceComponent>(ComponentTypes::INTERFACE_COMPONENT);

	const auto& menuObject = interfaceComponent->interfaceMenuObject();

	//If I am the current global interfaceObject, then clear the static variable
	if (parentObject == interfaceComponent->currentGameObjectInterfaceActive()) {
		interfaceComponent->clearCurrentGameObjectInterfaceActive();
	}

	//Enable Render
	menuObject.value()->disableRender();


}
