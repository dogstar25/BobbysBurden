#pragma once
#include "MobyDick.h"

class IMGuiDynamicInterfaceMenu : public IMGuiItem
{
public:
	IMGuiDynamicInterfaceMenu() = default;
	IMGuiDynamicInterfaceMenu(std::string gameObjectType, b2Vec2 padding, ImVec4 backgroundColor, ImVec4 textColor,
		ImVec4 buttonColor, ImVec4 buttonHoverColor, ImVec4 buttonActiveColor, bool autoSize);
	glm::vec2 render() override;

private:

	std::string m_label;

	void _buildInteractionRow(GameObject* playerObject, GameObject* interactiveGameObject);
	void _buildPuzzleRow(GameObject* playerObject, GameObject* interactiveGameObject);
	void _displayMousePointImage(ImVec4 color);
	void _displayKeyImage(std::string keyValue, ImVec4 color);
	void _displayPuzzlePieceImage(bool locked, ImVec4 color);


	

};