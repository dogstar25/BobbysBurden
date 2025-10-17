#include "IMGuiProximityHintMenu.h"

#include "BB_IMGuiUtil.h"
#include "../gameConstants.h"


extern std::unique_ptr<Game> game;

IMGuiProximityHintMenu::IMGuiProximityHintMenu(std::string gameObjectType, b2Vec2 padding, ImVec4 backgroundColor, ImVec4 textColor,
	ImVec4 buttonColor, ImVec4 buttonHoverColor, ImVec4 buttonActiveColor, bool autoSize) :
	IMGuiItem(gameObjectType, padding, backgroundColor, textColor, buttonColor, buttonHoverColor, buttonActiveColor, autoSize)
{

	m_flags = ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize;

}

glm::vec2 IMGuiProximityHintMenu::render()
{

	glm::vec2 windowSize{};
	bool showWindow = true;

	const auto& interfaceGameObject = parent()->parent();

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
		ImGui::textCentered(interfaceGameObject.value()->description().c_str());

		ImGui::PopFont();
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Spacing();

		//Set mouse Cursor
		auto cursor = TextureManager::instance().getMouseCursor("CURSOR_ARROW_QUESTION");
		SceneManager::instance().setMouseCursor(cursor);

		//Display a message about a nearby puzzle or item
		ImGui::PushFont(m_smallFont);
		ImGui::PushStyleColor(ImGuiCol_Text, util::SDLColorToImVec4(Colors::SAPPHIRE));

		ImGui::textCentered("There is something of interest ");
		ImGui::textCentered("near this location. Keep looking.");
		ImGui::NewLine();
		ImGui::textCentered("It may be very small and/or you ");
		ImGui::textCentered("may need to get closer.");

		ImGui::PopStyleColor();
		ImGui::PopFont();

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

void IMGuiProximityHintMenu::_buildInteractionRow(GameObject* onOffSwitchObject)
{
	static int buttonSeq{};

	const auto& onOffSwitchInterfaceComponent = onOffSwitchObject->getComponent<InterfaceComponent>(ComponentTypes::INTERFACE_COMPONENT);

	ImGui::PushFont(m_normalFont);

	//If the USE isAvailable, then show the green mouseclick image and the label that goes with the event
	if (onOffSwitchInterfaceComponent->isEventAvailable(Actions::USE)) {

		ImGui::displayMouseLeftClickImage(util::SDLColorToImVec4(Colors::EMERALD));
		ImGui::SameLine();

		//Show Open or Close based on the current state
		const auto& doorStateComponent = onOffSwitchObject->getComponent<StateComponent>(ComponentTypes::STATE_COMPONENT);

		if (doorStateComponent->testState(GameObjectState::ON)) {

			ImGui::TextWrapped("Turn Off");
				
		}
		else {
			ImGui::TextWrapped("Tuen On");

		}

	}
	else {

		ImGui::displayMouseLeftClickImage(util::SDLColorToImVec4(Colors::GREY));
		ImGui::SameLine();
		ImGui::TextColored(util::SDLColorToImVec4(Colors::GREY), "[Locked]");

	}

	ImGui::PopFont();

}

