#include "IMGuiOpenCloseReceptacleMenu.h"
#include "BB_IMGuiUtil.h"
#include "../gameConstants.h"



extern std::unique_ptr<Game> game;

IMGuiOpenCloseReceptacleMenu::IMGuiOpenCloseReceptacleMenu(std::string gameObjectType, b2Vec2 padding, ImVec4 backgroundColor, ImVec4 textColor,
	ImVec4 buttonColor, ImVec4 buttonHoverColor, ImVec4 buttonActiveColor, bool autoSize) :
	IMGuiItem(gameObjectType, padding, backgroundColor, textColor, buttonColor, buttonHoverColor, buttonActiveColor, autoSize)
{

	m_flags = ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize;

}

glm::vec2 IMGuiOpenCloseReceptacleMenu::render()
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

			_buildPuzzleRow(interfaceGameObject.value());

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

void IMGuiOpenCloseReceptacleMenu::_buildInteractionRow(GameObject* interfaceGameObject)
{
	static int buttonSeq{};

	const auto& puzzleComponent = interfaceGameObject->getComponent<PuzzleComponent>(ComponentTypes::PUZZLE_COMPONENT);
	const auto& interfaceComponent = interfaceGameObject->getComponent<InterfaceComponent>(ComponentTypes::INTERFACE_COMPONENT);

	ImGui::PushFont(m_normalFont);


	//If the USE isAvailable, then show the green mouseclick image and the label that goes with the event
	if (interfaceComponent->isEventAvailable(Actions::USE)) {

		ImGui::displayMouseLeftClickImage(util::SDLColorToImVec4(Colors::EMERALD));
		ImGui::SameLine();

		//Show Open or Close based on the current state
		if (interfaceGameObject->hasComponent(ComponentTypes::INVENTORY_COMPONENT)) {
			const auto& inventoryComponent = interfaceGameObject->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);

			if (inventoryComponent->isOpen() == false) {

				ImGui::TextWrapped("Open");
				
				auto cursor = TextureManager::instance().getMouseCursor("CURSOR_HAND_APPLY");
				SceneManager::instance().setMouseCursor(cursor);

			}
			else {
				ImGui::TextWrapped("Close");

				//Set mouse Cursor
				if (parent()->parent().value()->hasTrait(TraitTag::receptacle)) {

					auto cursor = TextureManager::instance().getMouseCursor("CURSOR_HAND_APPLY");
					SceneManager::instance().setMouseCursor(cursor);
				}

			}

		}

	}
	else {

		ImGui::displayMouseLeftClickImage(util::SDLColorToImVec4(Colors::GREY));
		ImGui::SameLine();
		ImGui::TextColored(util::SDLColorToImVec4(Colors::GREY), "[Locked]");

	}


	ImGui::PopFont();

}

void IMGuiOpenCloseReceptacleMenu::_buildPuzzleRow(GameObject* interfaceGameObject)
{
	static int buttonSeq{};

	const auto& puzzleComponent = interfaceGameObject->getComponent<PuzzleComponent>(ComponentTypes::PUZZLE_COMPONENT);

	//Use small Font
	ImGui::PushFont(m_smallFont);

	//Loop through all puzzles and display the status of the pieces
	for (const auto& puzzlePair : puzzleComponent->puzzles()) {

		//Clue text
		ImGui::PushStyleColor(ImGuiCol_Text, util::SDLColorToImVec4(Colors::CANDLE_LIGHT));
		ImGui::TextWrapped(puzzlePair.second->clue().c_str());
		ImGui::PopStyleColor();
		ImGui::NewLine();

		//Loop through all pieces and display the proper status image
		for (const auto& piecePair : puzzlePair.second->pieces()) {

			ImGui::SameLine();

			if (piecePair.second.isSolved == false) {
				ImGui::displayPuzzlePieceImage(true, util::SDLColorToImVec4(Colors::GREY));

			}
			else {
				ImGui::displayPuzzlePieceImage(false, util::SDLColorToImVec4(Colors::EMERALD));
			}

		}

	}

	ImGui::PopFont();

}