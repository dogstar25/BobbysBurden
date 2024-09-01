#include "BB_IMGuiFactory.h"
#include "IMGuiPauseWindow.h"
#include "IMGuiTitleScreenMenu.h"
#include "IMGuiTestLevelMenu.h"
#include "IMGuiDynamicInterfaceMenu.h"
#include "IMGuiOpenCloseDoorMenu.h"
#include "IMGuiItemContact.h"
#include "IMGuiOpenCloseReceptacleMenu.h"
#include "IMGuiOnOffToggleMenu.h"
#include "IMGuiProximityHintMenu.h"
#include "IMGuiGoUpDownMenu.h"
#include "IMGuiBobbyHideMenu.h"


BB_IMGuiFactory::BB_IMGuiFactory()
{

}


std::shared_ptr<IMGuiItem> BB_IMGuiFactory::create(std::string iMGuiItemType, GameObject* parent, std::string gameObjectType, b2Vec2 padding, ImVec4 backgroundColor, ImVec4 textColor,
	ImVec4 buttonColor, ImVec4 buttonHoverColor, ImVec4 buttonActiveColor, bool autoSize, std::string staticTextValue)
{
	std::shared_ptr<IMGuiItem> iMGuiItem;

	if (iMGuiItemType == "IMGuiPauseWindow") {
		iMGuiItem = std::make_shared<IMGuiPauseWindow>(gameObjectType, padding, backgroundColor, textColor, buttonColor, buttonHoverColor, buttonActiveColor, autoSize);
	}
	else if (iMGuiItemType == "IMGuiTitleScreenMenu") {
		iMGuiItem = std::make_shared<IMGuiTitleScreenMenu>(gameObjectType, padding, backgroundColor, textColor, buttonColor, buttonHoverColor, buttonActiveColor, autoSize);
	}
	else if (iMGuiItemType == "IMGuiTestLevelMenu") {
		iMGuiItem = std::make_shared<IMGuiTestLevelMenu>(gameObjectType, padding, backgroundColor, textColor, buttonColor, buttonHoverColor, buttonActiveColor, autoSize);
	}
	else if (iMGuiItemType == "IMGuiDynamicInterfaceMenu") {
		iMGuiItem = std::make_shared<IMGuiDynamicInterfaceMenu>(gameObjectType, padding, backgroundColor, textColor, buttonColor, buttonHoverColor, buttonActiveColor, autoSize);
	}
	else if (iMGuiItemType == "IMGuiOpenCloseDoorMenu") {
		iMGuiItem = std::make_shared<IMGuiOpenCloseDoorMenu>(gameObjectType, padding, backgroundColor, textColor, buttonColor, buttonHoverColor, buttonActiveColor, autoSize);
	}
	else if (iMGuiItemType == "IMGuiItemContact") {
		iMGuiItem = std::make_shared<IMGuiItemContact>(gameObjectType, padding, backgroundColor, textColor, buttonColor, buttonHoverColor, buttonActiveColor, autoSize);
	}
	else if (iMGuiItemType == "IMGuiOpenCloseReceptacleMenu") {
		iMGuiItem = std::make_shared<IMGuiOpenCloseReceptacleMenu>(gameObjectType, padding, backgroundColor, textColor, buttonColor, buttonHoverColor, buttonActiveColor, autoSize);
	}
	else if (iMGuiItemType == "IMGuiOnOffToggleMenu") {

		iMGuiItem = std::make_shared<IMGuiOnOffToggleMenu>(gameObjectType, padding, backgroundColor, textColor, buttonColor, buttonHoverColor, buttonActiveColor, autoSize);
	}
	else if (iMGuiItemType == "IMGuiProximityHintMenu") {

		iMGuiItem = std::make_shared<IMGuiProximityHintMenu>(gameObjectType, padding, backgroundColor, textColor, buttonColor, buttonHoverColor, buttonActiveColor, autoSize);
	}
	else if (iMGuiItemType == "IMGuiGoUpDownMenu") {

		iMGuiItem = std::make_shared<IMGuiGoUpDownMenu>(gameObjectType, padding, backgroundColor, textColor, buttonColor, buttonHoverColor, buttonActiveColor, autoSize);
	}
	else if (iMGuiItemType == "IMGuiBobbyHideMenu") {

		iMGuiItem = std::make_shared<IMGuiBobbyHideMenu>(gameObjectType, padding, backgroundColor, textColor, buttonColor, buttonHoverColor, buttonActiveColor, autoSize);
	}

	else {

		iMGuiItem = IMGuiFactory::create(iMGuiItemType, parent, gameObjectType, padding, backgroundColor, textColor, buttonColor, buttonHoverColor, buttonActiveColor, autoSize, staticTextValue);

	}

	iMGuiItem->setParent(parent);

	return iMGuiItem;

}
