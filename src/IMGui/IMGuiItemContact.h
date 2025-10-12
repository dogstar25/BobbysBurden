#pragma once
#include "MobyDick.h"

class IMGuiItemContact : public IMGuiItem
{
public:
	IMGuiItemContact() = default;
	IMGuiItemContact(std::string gameObjectType, b2Vec2 padding, ImVec4 backgroundColor, ImVec4 textColor,
		ImVec4 buttonColor, ImVec4 buttonHoverColor, ImVec4 buttonActiveColor, bool autoSize);
	glm::vec2 render() override;

private:

	std::string m_label;

	void _buildActionRow(GameObject* interfacedObject);
	void _displayPuzzleGui(GameObject* puzzleTouched);
	void _displayInventoryGui(GameObject* puzzleTouched);

	

};