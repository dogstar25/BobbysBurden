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

	const auto& renderComponent = parent()->getComponent<RenderComponent>(ComponentTypes::RENDER_COMPONENT);
	const auto& actionComponent = parent()->parent().value()->getComponent<ActionComponent>(ComponentTypes::ACTION_COMPONENT);

	const auto& player = parent()->parentScene()->getFirstGameObjectByTrait(TraitTag::player);
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
		
		ImGui::SetWindowPos(ImVec2{ renderComponent->getRenderDestRect().x, renderComponent->getRenderDestRect().y });

		//Build the description
		ImGui::PushFont(m_smallGothicFont);
		ImGui::textCentered(interfaceGameObject.value()->description().c_str());
		ImGui::PopFont();
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Spacing();	

		//Default interaction action
		_buildInteractionRow(player->get(), interfaceGameObject.value());

		//If we have puzzle info the show then show it
		if (interfaceGameObject.value()->hasComponent(ComponentTypes::PUZZLE_COMPONENT)) {
			_buildPuzzleRow(player->get(), interfaceGameObject.value());
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

void IMGuiDynamicInterfaceMenu::_buildInteractionRow(GameObject* playerObject, GameObject* interfaceGameObject)
{
	static int buttonSeq{};

	const auto& puzzleComponent = interfaceGameObject->getComponent<PuzzleComponent>(ComponentTypes::PUZZLE_COMPONENT);
	const auto& interfaceComponent = interfaceGameObject->getComponent<InterfaceComponent>(ComponentTypes::INTERFACE_COMPONENT);
	const auto clickEvent = interfaceComponent->eventActions().at(Actions::USE);

	ImGui::PushFont(m_normalFont);


	//If the OnClick isAvailable, then show the green mouseclick image and the label that goes with the event
	if (interfaceComponent->isEventAvailable(Actions::USE)) {

		_displayMousePointImage(util::SDLColorToImVec4(Colors::EMERALD));
		ImGui::SameLine();
		ImGui::TextWrapped(clickEvent->label.c_str());
	}
	else {

		_displayMousePointImage(util::SDLColorToImVec4(Colors::GREY));
		ImGui::SameLine();
		ImGui::TextColored(util::SDLColorToImVec4(Colors::GREY), "[Locked]");

	}

	ImGui::PopFont();

}

void IMGuiDynamicInterfaceMenu::_buildPuzzleRow(GameObject* playerObject, GameObject* interfaceGameObject)
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
				_displayPuzzlePieceImage(true, util::SDLColorToImVec4(Colors::GREY));

			}
			else {
				_displayPuzzlePieceImage(false, util::SDLColorToImVec4(Colors::EMERALD));
			}

		}

	}

	ImGui::PopFont();

}

void IMGuiDynamicInterfaceMenu::_displayMousePointImage(ImVec4 color)
{

	//TextureAtlas Coordinates
	glm::vec2 topLeft = util::glNormalizeTextureCoords({ 177,65 }, { 256, 256 });
	glm::vec2 bottomRight = util::glNormalizeTextureCoords({ 240,128 }, { 256, 256 });

	if (GameConfig::instance().rendererType() == RendererType::OPENGL) {

		GLuint64 textureAtlasId = static_cast<GLRenderer*>(game->renderer())->getTextureId(GL_TextureIndexType::IMGUI_TEXTURE_ATLAS);
		ImGui::Image((void*)textureAtlasId, ImVec2(32, 32), ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color);
	}
	else {

		//SDL2 Texture void* is the SDL_Texture*
		SDL_Texture* sdlTexture = TextureManager::instance().getTexture("TEXTURE_IMGUI_ATLAS")->sdlTexture;
		ImGui::Image((void*)(SDL_Texture*)sdlTexture, ImVec2(32, 32), ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color);
	}
}

void IMGuiDynamicInterfaceMenu::_displayPuzzlePieceImage( bool locked, ImVec4 color)
{
	glm::vec2 topLeft{};
	glm::vec2 bottomRight{};

	//TextureAtlas Coordinates
	if (locked) {
		topLeft = util::glNormalizeTextureCoords({ 47,65 }, { 256, 256 });
		bottomRight = util::glNormalizeTextureCoords({ 110,128 }, { 256, 256 });
	}
	else {
		topLeft = util::glNormalizeTextureCoords({ 47,130 }, { 256, 256 });
		bottomRight = util::glNormalizeTextureCoords({ 110,193 }, { 256, 256 });
	}

	if (GameConfig::instance().rendererType() == RendererType::OPENGL) {

		GLuint64 textureAtlasId = static_cast<GLRenderer*>(game->renderer())->getTextureId(GL_TextureIndexType::IMGUI_TEXTURE_ATLAS);
		ImGui::Image((void*)textureAtlasId, ImVec2(32, 32), ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color);
	}
	else {

		//SDL2 Texture void* is the SDL_Texture*
		SDL_Texture* sdlTexture = TextureManager::instance().getTexture("TEXTURE_IMGUI_ATLAS")->sdlTexture;
		ImGui::Image((void*)(SDL_Texture*)sdlTexture, ImVec2(32, 32), ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color);
	}

}

void IMGuiDynamicInterfaceMenu::_displayKeyImage(std::string keyValue, ImVec4 color)
{

	//TextureAtlas Coordinates for bar
	glm::vec2 topLeft = util::glNormalizeTextureCoords({ 177,0 }, { 256, 256 });
	glm::vec2 bottomRight = util::glNormalizeTextureCoords({ 240,63 }, { 256, 256 });

	if (GameConfig::instance().rendererType() == RendererType::OPENGL) {

		GLuint64 textureAtlasId = static_cast<GLRenderer*>(game->renderer())->getTextureId(GL_TextureIndexType::IMGUI_TEXTURE_ATLAS);
		ImGui::Image((void*)textureAtlasId, ImVec2(32, 32), ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color);
	}
	else {

		//SDL2 Texture void* is the SDL_Texture*
		SDL_Texture* sdlTexture = TextureManager::instance().getTexture("TEXTURE_IMGUI_ATLAS")->sdlTexture;
		ImGui::Image((void*)(SDL_Texture*)sdlTexture, ImVec2(24, 24), ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color);
	}

	ImGui::SameLine();

	ImGui::adjustCursorPosition(-24.0, 2.0);

	//Keyboard key value
	ImGui::Text(keyValue.c_str());
}

