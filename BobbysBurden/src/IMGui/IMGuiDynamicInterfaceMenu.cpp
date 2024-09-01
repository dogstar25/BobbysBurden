#include "IMGuiDynamicInterfaceMenu.h"
#include "BB_IMGuiUtil.h"
#include "../GameConstants.h"
#include "../BBContextManager.h"



extern std::unique_ptr<Game> game;

IMGuiDynamicInterfaceMenu::IMGuiDynamicInterfaceMenu(std::string gameObjectType, b2Vec2 padding, ImVec4 backgroundColor, ImVec4 textColor,
	ImVec4 buttonColor, ImVec4 buttonHoverColor, ImVec4 buttonActiveColor, bool autoSize) :
	IMGuiItem(gameObjectType, padding, backgroundColor, textColor, buttonColor, buttonHoverColor, buttonActiveColor, autoSize)
{

	m_flags = ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize;

}

glm::vec2 IMGuiDynamicInterfaceMenu::render()
{

	glm::vec2 windowSize{};
	bool showWindow = true;

	const auto& interfaceGameObject = parent()->parent();
	const auto& renderComponent = parent()->getComponent<RenderComponent>(ComponentTypes::RENDER_COMPONENT);
	const auto& actionComponent = interfaceGameObject.value()->getComponent<ActionComponent>(ComponentTypes::ACTION_COMPONENT);
	const auto& player = parent()->parentScene()->getFirstGameObjectByTrait(TraitTag::player);
	

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
		
		ImGui::SetWindowPos(ImVec2{ renderComponent->getRenderDestRect().x, renderComponent->getRenderDestRect().y });

		//Build the description
		ImGui::PushFont(m_smallGothicFont);
		ImGui::textCentered(interfaceGameObject.value()->description().c_str());
		ImGui::PopFont();
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Spacing();	

		//Default interaction action
		_buildInteractionRow(interfaceGameObject.value());

		//If we have puzzle info the show then show it
		if (interfaceGameObject.value()->hasComponent(ComponentTypes::PUZZLE_COMPONENT)) {

			//Use small Font
			ImGui::PushFont(m_smallFont);

			ImGui::_buildPuzzleRow(interfaceGameObject.value());

			ImGui::PopFont();

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

void IMGuiDynamicInterfaceMenu::_buildInteractionRow(GameObject* interfaceGameObject)
{
	static int buttonSeq{};

	const auto& puzzleComponent = interfaceGameObject->getComponent<PuzzleComponent>(ComponentTypes::PUZZLE_COMPONENT);
	const auto& interfaceComponent = interfaceGameObject->getComponent<InterfaceComponent>(ComponentTypes::INTERFACE_COMPONENT);


	std::shared_ptr<InterfaceAction> clickEvent;

	if (interfaceComponent->hasEvent(Actions::USE)) {

		clickEvent = interfaceComponent->eventActions().at(Actions::USE);
	}

	ImGui::PushFont(m_normalFont);


	//If the OnClick isAvailable, then show the green mouseclick image and the label that goes with the event
	if (interfaceComponent->hasEvent(Actions::USE)) {
		if (interfaceComponent->isEventAvailable(Actions::USE)) {

			ImGui::displayMouseLeftClickImage(util::SDLColorToImVec4(Colors::EMERALD));
			ImGui::SameLine();
			ImGui::TextWrapped(clickEvent->label.c_str());

			//set the cursor
			auto cursor = TextureManager::instance().getMouseCursor("CURSOR_POINTING");
			SceneManager::instance().setMouseCursor(cursor);

		}
		else {

			ImGui::displayMouseLeftClickImage(util::SDLColorToImVec4(Colors::GREY));
			ImGui::SameLine();
			ImGui::TextColored(util::SDLColorToImVec4(Colors::GREY), "[Locked]");

		}
	}

	ImGui::PopFont();

}



