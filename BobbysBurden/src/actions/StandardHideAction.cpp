#include "StandardHideAction.h"


void StandardHideAction::perform(GameObject* parentObject)
{

	//Get the Puzzle Interface Menu
	const auto& menuObject =
		parentObject->getComponent<InterfaceComponent>(ComponentTypes::INTERFACE_COMPONENT)->interfaceMenuObject();

	//Enable Render
	menuObject.value()->disableRender();


}
