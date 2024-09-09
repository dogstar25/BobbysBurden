#include "HideInterfaceAction.h"
#include "../components/BBInterfaceComponent.h"


void HideInterfaceAction::perform()
{

	const auto& interfaceComponent = m_parent->getComponent<BBInterfaceComponent>(ComponentTypes::INTERFACE_COMPONENT);

	const auto& menuObject = interfaceComponent->interfaceMenuObject();

	//If I am the current global interfaceObject, then clear the static variable
	if (m_parent == interfaceComponent->currentGameObjectInterfaceActive()) {
		interfaceComponent->clearCurrentGameObjectInterfaceActive();
	}

	//Enable Render
	menuObject.value()->disableRender();


}
