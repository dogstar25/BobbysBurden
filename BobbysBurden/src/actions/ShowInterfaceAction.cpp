#include "ShowInterfaceAction.h"
#include "../components/BBInterfaceComponent.h"


void ShowInterfaceAction::perform(GameObject* gameObject)
{

	////Build a Puzzle Interface Menu
	//std::shared_ptr<GameObject> menuObject = 
	//	std::make_shared<GameObject>("GENERIC_INTERFACE_MENU", (float)-50.0, (float)-50.0, (float)0, 
	//		parentObject->parentScene(), GameLayer::MAIN);

	//Get the Puzzle Interface Menu
	const auto& interfaceComponent =
		gameObject->getComponent<BBInterfaceComponent>(ComponentTypes::INTERFACE_COMPONENT);
	const auto& menuObject =
		interfaceComponent->interfaceMenuObject();


	if (menuObject.has_value()) {
		//Enable Render
		menuObject.value()->enableRender();

		//Get the Main frame object where we're gonna show this menu
		//const auto& mainFrame = gameObject->parentScene()->getFirstGameObjectByName("MainHudFrame");
		const auto& mainFrame = gameObject->parentScene()->getFirstGameObjectByType("HUD_INTERFACE_FRAME");

		if (mainFrame.has_value()) {
			menuObject.value()->setPosition(mainFrame.value()->getCenterPosition());
		}

	}

}
