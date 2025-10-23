#include "IMGuiGoUpDownMenu.h"
#include "BB_IMGuiUtil.h"
#include "../gameConstants.h"



//extern std::unique_ptr<Game> game;

IMGuiGoUpDownMenu::IMGuiGoUpDownMenu(std::string gameObjectType, b2Vec2 padding, ImVec4 backgroundColor, ImVec4 textColor,
	ImVec4 buttonColor, ImVec4 buttonHoverColor, ImVec4 buttonActiveColor, bool autoSize) :
	IMGuiItem(gameObjectType, padding, backgroundColor, textColor, buttonColor, buttonHoverColor, buttonActiveColor, autoSize)
{

	m_flags = ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize;

}

glm::vec2 IMGuiGoUpDownMenu::render()
{

	glm::vec2 windowSize{};
	bool showWindow = true;

	const auto& stairsGameObject = parent()->parent();
	const auto& renderComponent = parent()->getComponent<RenderComponent>(ComponentTypes::RENDER_COMPONENT);


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

		//ImGui::SetWindowPos(ImVec2{ renderComponent->getRenderDestRect().x, renderComponent->getRenderDestRect().y });

		//Build the description
		ImGui::PushFont(m_smallGothicFont);
		ImGui::textCentered(stairsGameObject.value()->description().c_str());
		ImGui::PopFont();
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Spacing();

		//Default interaction action
		_buildInteractionRow();

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

void IMGuiGoUpDownMenu::_buildInteractionRow()
{
	static int buttonSeq{};

	ImGui::PushFont(m_normalFont);

	ImGui::displayUpArrowImage(util::SDLColorToImVec4(Colors::EMERALD));
	ImGui::SameLine();
	ImGui::Text("%s", "Up");
				
	ImGui::displayDownArrowImage(util::SDLColorToImVec4(Colors::EMERALD));
	ImGui::SameLine();
	ImGui::Text("Down");

	ImGui::PopFont();

}
