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

		//Build the description
		

		if (interfaceGameObject.value()->hasTrait(TraitTag::loose) && interfaceGameObject.value()->isTouchingByTrait(TraitTag::player) == false) {

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
	if (interfacedObject->hasTrait(TraitTag::draggable)) {

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
	//If this item has the "obtainable" trait then show the Take action
	if ((interfacedObject->hasTrait(TraitTag::loose) == false && interfacedObject->hasTrait(TraitTag::obtainable)) ||
		(interfacedObject->hasTrait(TraitTag::loose) == true && interfacedObject->isTouchingByTrait(TraitTag::player)) ) {

		ImGui::displayMouseRightClickImage(util::SDLColorToImVec4(Colors::EMERALD));
		ImGui::SameLine();

		ImGui::TextWrapped("Take");

		auto cursor = TextureManager::instance().getMouseCursor("CURSOR_HAND_GRAB_1");
		SceneManager::instance().setMouseCursor(cursor);


	}


	ImGui::PopFont();



}




