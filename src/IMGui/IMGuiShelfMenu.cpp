#include "IMGuiShelfMenu.h"

#include "BB_IMGuiUtil.h"
#include "../gameConstants.h"


extern std::unique_ptr<Game> game;

IMGuiShelfMenu::IMGuiShelfMenu(std::string gameObjectType, b2Vec2 padding, ImVec4 backgroundColor, ImVec4 textColor,
	ImVec4 buttonColor, ImVec4 buttonHoverColor, ImVec4 buttonActiveColor, bool autoSize) :
	IMGuiItem(gameObjectType, padding, backgroundColor, textColor, buttonColor, buttonHoverColor, buttonActiveColor, autoSize)
{

	m_flags = ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize;

}

glm::vec2 IMGuiShelfMenu::render()
{

	glm::vec2 windowSize{};
	bool showWindow = true;

	const auto& onOffSwitchObject = parent()->parent();

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	setWindowProperties(parent());

	//Set color
	ImGui::PushStyleColor(ImGuiCol_WindowBg, m_backgroundColor);
	ImGui::PushStyleColor(ImGuiCol_Button, m_buttonColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_buttonHoverColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_buttonActiveColor);
	ImGui::PushStyleColor(ImGuiCol_Text, m_textColor);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

	ImGui::Begin(m_gameObjectType.c_str(), &showWindow, m_flags);
	{

		//Build the description
		ImGui::PushFont(m_smallGothicFont);
		std::string description = "Shelf";
		ImGui::textCentered(description);
		ImGui::PopFont();
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Spacing();

		//Set mouse Cursor
		//auto cursor = TextureManager::instance().getMouseCursor("CURSOR_POINTING");
		//SceneManager::instance().setMouseCursor(cursor);

		//Default interaction action
		_buildInteractionRow(onOffSwitchObject.value());

		//If we have puzzle info the show then show it
		if (onOffSwitchObject.value()->hasComponent(ComponentTypes::PUZZLE_COMPONENT)) {

			ImGui::_buildPuzzleRow(onOffSwitchObject.value());

		}

		//Capture this imGui window size
		windowSize = { ImGui::GetWindowSize().x, ImGui::GetWindowSize().y };

	}
	ImGui::End();

	//pop color style
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();

	return windowSize;
}

void IMGuiShelfMenu::_buildInteractionRow(GameObject* onOffSwitchObject)
{
	static int buttonSeq{};

	const auto& onOffSwitchInterfaceComponent = onOffSwitchObject->getComponent<InterfaceComponent>(ComponentTypes::INTERFACE_COMPONENT);

	ImGui::PushFont(m_normalFont);

	ImGui::TextWrapped("You can place items here.");

	ImGui::PopFont();

}

