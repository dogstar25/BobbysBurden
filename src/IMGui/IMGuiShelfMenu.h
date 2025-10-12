#pragma once

#include "MobyDick.h"


class IMGuiShelfMenu : public IMGuiItem
{
public:
	IMGuiShelfMenu() = default;
	IMGuiShelfMenu(std::string gameObjectType, b2Vec2 padding, ImVec4 backgroundColor, ImVec4 textColor,
		ImVec4 buttonColor, ImVec4 buttonHoverColor, ImVec4 buttonActiveColor, bool autoSize);
	glm::vec2 render() override;

private:

	std::string m_label;
	void _buildInteractionRow(GameObject* interactiveGameObject);


};