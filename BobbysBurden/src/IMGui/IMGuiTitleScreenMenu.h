#pragma once
#include "MobyDick.h"


class IMGuiTitleScreenMenu : public IMGuiItem
{
public:
	IMGuiTitleScreenMenu() = default;
	IMGuiTitleScreenMenu(std::string gameObjectType, b2Vec2 padding, ImVec4 backgroundColor, ImVec4 textColor, ImVec4 buttonColor, ImVec4 buttonHoverColor, ImVec4 buttonActiveColor,
		bool autoSize);
	glm::vec2 render() override;
	void settingsModal();
	void apply(int mouseSensitivity, int soundVolume);
	//void loadPlaySceneAndLevel(int level=0);

	ImFont* m_font{};

private:
	ImVec2 m_settingsModalSize{ 332,275 };
	ImGuiWindowFlags m_SettingsModalflags{ ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove };

};


