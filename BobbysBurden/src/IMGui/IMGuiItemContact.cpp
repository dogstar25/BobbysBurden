#include "IMGuiItemContact.h"
#include "BB_IMGuiUtil.h"
#include "../GameConstants.h"
#include "../BBContextManager.h"



extern std::unique_ptr<Game> game;

IMGuiItemContact::IMGuiItemContact(std::string gameObjectType, b2Vec2 padding, ImVec4 backgroundColor, ImVec4 textColor,
	ImVec4 buttonColor, ImVec4 buttonHoverColor, ImVec4 buttonActiveColor, bool autoSize) :
	IMGuiItem(gameObjectType, padding, backgroundColor, textColor, buttonColor, buttonHoverColor, buttonActiveColor, autoSize)
{

	m_flags = ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize;

}

glm::vec2 IMGuiItemContact::render()
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

		//
		if (interfaceGameObject.value()->isDragging()) {
			SDL_ShowCursor(SDL_FALSE);
		}
		

		if (interfaceGameObject.value()->isDragging() == false && 
			interfaceGameObject.value()->hasTrait(TraitTag::loose) && 
			interfaceGameObject.value()->isTouchingByTrait(TraitTag::player) == false) {

			ImGui::PushFont(m_normalFont);
			ImGui::textCentered("???");
		}
		else {
			ImGui::PushFont(m_smallGothicFont);
			ImGui::textCentered(interfaceGameObject.value()->description().c_str());
		}
			
		
		ImGui::PopFont();
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Spacing();	



		_buildActionRow(interfaceGameObject.value());


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


void IMGuiItemContact::_buildActionRow(GameObject* interfacedObject)
{

	ImGui::PushFont(m_normalFont);

	//If this item has the "draggable" trait then show the Grab action
	if (interfacedObject->hasTrait(TraitTag::draggable) && interfacedObject->isDragging() == false) {

		//If this is an object inside of an inventory OR its a loose item and touched by the player
		if (interfacedObject->hasTrait(TraitTag::loose) && interfacedObject->isTouchingByTrait(TraitTag::player) ||
			interfacedObject->hasTrait(TraitTag::loose) == false) {
			ImGui::displayMouseLeftClickImage(util::SDLColorToImVec4(Colors::EMERALD));
			ImGui::SameLine();

			ImGui::TextWrapped("Grab");

			auto cursor = TextureManager::instance().getMouseCursor("CURSOR_HAND_GRAB_1");
			SceneManager::instance().setMouseCursor(cursor);
			ImGui::SameLine();
			//ImGui::Spacing();
			ImGui::Dummy({ 3,0 });
			ImGui::SameLine();
		}

	}
	//If this item has the "obtainable" trait then show the Take action
	if (interfacedObject->isDragging() == false &&
		(interfacedObject->hasTrait(TraitTag::loose) == false && interfacedObject->hasTrait(TraitTag::obtainable) ||
		interfacedObject->hasTrait(TraitTag::loose) == true && interfacedObject->isTouchingByTrait(TraitTag::player)) ) {

		ImGui::displayMouseRightClickImage(util::SDLColorToImVec4(Colors::EMERALD));
		ImGui::SameLine();

		ImGui::TextWrapped("Take");

		auto cursor = TextureManager::instance().getMouseCursor("CURSOR_HAND_GRAB_1");
		SceneManager::instance().setMouseCursor(cursor);


	}

	if (interfacedObject->hasTrait(TraitTag::puzzle_item) && interfacedObject->isTouchingByTrait(TraitTag::puzzle)) {

		const auto& puzzleTouched = interfacedObject->getFirstTouchingByTrait(TraitTag::puzzle);

		if (puzzleTouched.value().lock()->isTouchingByTrait(TraitTag::player)) {


			ImGui::displayDropItemImage(util::SDLColorToImVec4(Colors::EMERALD));
			ImGui::SameLine();

			ImGui::Text("Apply To");
			ImGui::SameLine();
			ImGui::TextColored(util::SDLColorToImVec4(Colors::EMERALD), puzzleTouched.value().lock()->description().c_str());

			auto cursor = TextureManager::instance().getMouseCursor("CURSOR_HAND_APPLY_2");
			SceneManager::instance().setMouseCursor(cursor);
			SDL_ShowCursor(SDL_TRUE);
		}

	}

	if (interfacedObject->isDragging() == true &&
		interfacedObject->hasTrait(TraitTag::puzzle_item) && interfacedObject->isTouchingByTrait(TraitTag::inventory)) {

		const auto& inventoryTouched = interfacedObject->getFirstTouchingByTrait(TraitTag::inventory);

		//Only show the Drop icon if its the players inventory OR we are touching the objects with the inventory
		
		if (inventoryTouched.value().lock()->hasTrait(TraitTag::player_inventory) ||
			inventoryTouched.value().lock()->isTouchingByTrait(TraitTag::player)) {

			std::string receptacleDescription = inventoryTouched.value().lock()->description();

			ImGui::displayDropItemImage(util::SDLColorToImVec4(Colors::EMERALD));
			ImGui::SameLine();

			ImGui::Text("Drop In");
			ImGui::SameLine();
			ImGui::TextColored(util::SDLColorToImVec4(Colors::EMERALD), receptacleDescription.c_str());

			if (inventoryTouched.value().lock()->hasTrait(TraitTag::receptacle)) {
				auto cursor = TextureManager::instance().getMouseCursor("CURSOR_HAND_APPLY_2");
				SceneManager::instance().setMouseCursor(cursor);
				SDL_ShowCursor(SDL_TRUE);
			}
		}

	}


	ImGui::PopFont();



}



