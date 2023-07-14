#include "ShowPuzzleInterfaceAction.h"


void ShowPuzzleInterfaceAction::perform(GameObject* gameObject)
{

	////Build a Puzzle Interface Menu
	//std::shared_ptr<GameObject> menuObject = 
	//	std::make_shared<GameObject>("GENERIC_INTERFACE_MENU", (float)-50.0, (float)-50.0, (float)0, 
	//		parentObject->parentScene(), GameLayer::MAIN);

	//Get the Puzzle Interface Menu
	const auto& menuObject =
		gameObject->getComponent<InterfaceComponent>(ComponentTypes::INTERFACE_COMPONENT)->interfaceMenuObject();

	//Enable Render
	menuObject.value()->enableRender();

	//Get the Main frame object where we're gonna show this menu
	const auto& mainFrame = gameObject->parentScene()->getFirstGameObjectByName("MainHudFrame");

	if (mainFrame.has_value()) {
		menuObject.value()->setPosition(mainFrame.value()->getCenterPosition());
	}


}
