#include "IMGuiBobbyHideMenu.h"
#include "BB_IMGuiUtil.h"
#include "../gameConstants.h"



//extern std::unique_ptr<Game> game;

IMGuiBobbyHideMenu::IMGuiBobbyHideMenu(std::string gameObjectType, b2Vec2 padding, ImVec4 backgroundColor, ImVec4 textColor,
	ImVec4 buttonColor, ImVec4 buttonHoverColor, ImVec4 buttonActiveColor, bool autoSize) :
	IMGuiItem(gameObjectType, padding, backgroundColor, textColor, buttonColor, buttonHoverColor, buttonActiveColor, autoSize)
{

	m_flags = ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize;

}

glm::vec2 IMGuiBobbyHideMenu::render()
{

	glm::vec2 windowSize{};
	bool showWindow = true;

	const auto& hideInGameObject = parent()->parent();
	const auto& renderComponent = parent()->getComponent<RenderComponent>(ComponentTypes::RENDER_COMPONENT);
	const auto& player = parent()->parentScene()->player();


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
		ImGui::textCentered(hideInGameObject.value()->description().c_str());
		ImGui::PopFont();
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Spacing();

		//Default interaction action
		_buildInteractionRow(hideInGameObject.value());

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

void IMGuiBobbyHideMenu::_buildInteractionRow(GameObject* hideInGameObject)
{
	static int buttonSeq{};

	const auto& hidingSpotInterfaceComponent = parent()->parent().value()->getComponent<InterfaceComponent>(ComponentTypes::INTERFACE_COMPONENT);
	const auto& playerObject = parent()->parentScene()->player();

	ImGui::PushFont(m_normalFont);

	//If the USE isAvailable, then show the green mouseclick image and the label that goes with the event
	if (hidingSpotInterfaceComponent->isEventAvailable(Actions::USE)) {

		ImGui::displayMouseLeftClickImage(util::SDLColorToImVec4(Colors::EMERALD));
		ImGui::SameLine();

		if (playerObject->hasState(GameObjectState::HIDING)) {

			ImGui::Text("%s", "Unhide");
				
			auto cursor = TextureManager::instance().getMouseCursor("CURSOR_UNHIDE");
			SceneManager::instance().setMouseCursor(cursor);

		}
		else {
			ImGui::Text("%s", "Hide!");

			//Set mouse Cursor
			auto cursor = TextureManager::instance().getMouseCursor("CURSOR_HIDE");
			SceneManager::instance().setMouseCursor(cursor);

		}

	}
	else {

		ImGui::displayMouseLeftClickImage(util::SDLColorToImVec4(Colors::GREY));
		ImGui::SameLine();
		ImGui::TextColored(util::SDLColorToImVec4(Colors::GREY), "[Locked]");

	}


	ImGui::PopFont();

}
