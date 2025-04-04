#include "BB_IMGuiUtil.h"
#include "../GameConstants.h"
#include "../BBContextManager.h"
#include "../BBGameStateManager.h"

extern std::unique_ptr<Game> game;

namespace ImGui
{

	void continueGameLoad()
	{

		//Get the current level from the saveGame file
		game->gameStateMananger()->loadGame();

		//Send change to SCENE_PLAY Event
		util::sendSceneEvent(SCENE_ACTION_REPLACE, "SCENE_PLAY");

	}

	void newGameLoad()
	{

		game->gameStateMananger()->loadGamePrimerFile();

		//Send change to Play Scene Event
		util::sendSceneEvent(SCENE_ACTION_REPLACE, "SCENE_PLAY");

	}

	void displayMouseLeftClickImage(ImVec4 color)
	{

		//TextureAtlas Coordinates
		glm::vec2 topLeft = util::glNormalizeTextureCoords({ 131,65 }, { 512, 256 });
		glm::vec2 bottomRight = util::glNormalizeTextureCoords({ 194,128 }, { 512, 256 });

		if (GameConfig::instance().rendererType() == RendererType::OPENGL) {

			auto openGlTexture = TextureManager::instance().getTextureAtlas("textureAtlas_ImGui");
			GLuint64 textureAtlasId = static_cast<OpenGLTexture*>(openGlTexture.get())->textureId;
			ImGui::Image((void*)textureAtlasId, ImVec2(32, 32), ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color);
		}
		else {

			std::shared_ptr<Texture> texture = TextureManager::instance().getTextureAtlas("textureAtlas_ImGui");
			SDL_Texture* sdlTexture = std::static_pointer_cast<SDLTexture>(texture).get()->sdlTexture;
			
			ImGui::Image((void*)(SDL_Texture*)sdlTexture, ImVec2(32, 32), ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color);
		}
	}

	void displayMouseRightClickImage(ImVec4 color)
	{

		//TextureAtlas Coordinates
		glm::vec2 topLeft = util::glNormalizeTextureCoords({ 66,140 }, { 512, 256 });
		glm::vec2 bottomRight = util::glNormalizeTextureCoords({ 129,203 }, { 512, 256 });

		if (GameConfig::instance().rendererType() == RendererType::OPENGL) {

			auto openGlTexture = TextureManager::instance().getTextureAtlas("textureAtlas_ImGui");
			GLuint64 textureAtlasId = static_cast<OpenGLTexture*>(openGlTexture.get())->textureId;
			ImGui::Image((void*)textureAtlasId, ImVec2(32, 32), ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color);
		}
		else {

			std::shared_ptr<Texture> texture = TextureManager::instance().getTextureAtlas("textureAtlas_ImGui");
			SDL_Texture* sdlTexture = std::static_pointer_cast<SDLTexture>(texture).get()->sdlTexture;
			ImGui::Image((void*)(SDL_Texture*)sdlTexture, ImVec2(32, 32), ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color);
		}
	}

	void displayUpArrowImage(ImVec4 color)
	{

		//TextureAtlas Coordinates
		glm::vec2 topLeft = util::glNormalizeTextureCoords({ 131,140 }, { 512, 256 });
		glm::vec2 bottomRight = util::glNormalizeTextureCoords({ 194,203 }, { 512, 256 });

		if (GameConfig::instance().rendererType() == RendererType::OPENGL) {

			auto openGlTexture = TextureManager::instance().getTextureAtlas("textureAtlas_ImGui");
			GLuint64 textureAtlasId = static_cast<OpenGLTexture*>(openGlTexture.get())->textureId;
			ImGui::Image((void*)textureAtlasId, ImVec2(32, 32), ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color);
		}
		else {

			std::shared_ptr<Texture> texture = TextureManager::instance().getTextureAtlas("textureAtlas_ImGui");
			SDL_Texture* sdlTexture = std::static_pointer_cast<SDLTexture>(texture).get()->sdlTexture;
			ImGui::Image((void*)(SDL_Texture*)sdlTexture, ImVec2(32, 32), ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color);
		}
	}

	void displayDownArrowImage(ImVec4 color)
	{

		//TextureAtlas Coordinates
		glm::vec2 topLeft = util::glNormalizeTextureCoords({ 196,140 }, { 512, 256 });
		glm::vec2 bottomRight = util::glNormalizeTextureCoords({ 259,203 }, { 512, 256 });

		if (GameConfig::instance().rendererType() == RendererType::OPENGL) {

			auto openGlTexture = TextureManager::instance().getTextureAtlas("textureAtlas_ImGui");
			GLuint64 textureAtlasId = static_cast<OpenGLTexture*>(openGlTexture.get())->textureId;
			ImGui::Image((void*)textureAtlasId, ImVec2(32, 32), ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color);
		}
		else {

			std::shared_ptr<Texture> texture = TextureManager::instance().getTextureAtlas("textureAtlas_ImGui");
			SDL_Texture* sdlTexture = std::static_pointer_cast<SDLTexture>(texture).get()->sdlTexture;
			ImGui::Image((void*)(SDL_Texture*)sdlTexture, ImVec2(32, 32), ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color);
		}
	}

	void displayPuzzlePieceImage(bool locked, ImVec4 color)
	{
		glm::vec2 topLeft{};
		glm::vec2 bottomRight{};

		//TextureAtlas Coordinates
		if (locked) {
			topLeft = util::glNormalizeTextureCoords({ 1,65 }, { 512, 256 });
			bottomRight = util::glNormalizeTextureCoords({ 64,128 }, { 512, 256 });
		}
		else {
			topLeft = util::glNormalizeTextureCoords({ 1,130 }, { 512, 256 });
			bottomRight = util::glNormalizeTextureCoords({ 64,193 }, { 512, 256 });
		}

		if (GameConfig::instance().rendererType() == RendererType::OPENGL) {

			auto openGlTexture = TextureManager::instance().getTextureAtlas("textureAtlas_ImGui");
			GLuint64 textureAtlasId = static_cast<OpenGLTexture*>(openGlTexture.get())->textureId;
			ImGui::Image((void*)textureAtlasId, ImVec2(32, 32), ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color);
		}
		else {

			std::shared_ptr<Texture> texture = TextureManager::instance().getTextureAtlas("textureAtlas_ImGui");
			SDL_Texture* sdlTexture = std::static_pointer_cast<SDLTexture>(texture).get()->sdlTexture;
			ImGui::Image((void*)(SDL_Texture*)sdlTexture, ImVec2(32, 32), ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color);
		}

	}

	void displayDropItemImage(ImVec4 color)
	{

		//TextureAtlas Coordinates for bar
		glm::vec2 topLeft = util::glNormalizeTextureCoords({ 196,0 }, { 512, 256 });
		glm::vec2 bottomRight = util::glNormalizeTextureCoords({ 259,63 }, { 512, 256 });

		if (GameConfig::instance().rendererType() == RendererType::OPENGL) {

			auto openGlTexture = TextureManager::instance().getTextureAtlas("textureAtlas_ImGui");
			GLuint64 textureAtlasId = static_cast<OpenGLTexture*>(openGlTexture.get())->textureId;
			ImGui::Image((void*)textureAtlasId, ImVec2(32, 32), ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color);
		}
		else {

			std::shared_ptr<Texture> texture = TextureManager::instance().getTextureAtlas("textureAtlas_ImGui");
			SDL_Texture* sdlTexture = std::static_pointer_cast<SDLTexture>(texture).get()->sdlTexture;
			ImGui::Image((void*)(SDL_Texture*)sdlTexture, ImVec2(32, 32), ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color);
		}

	}

	void displayDropItemIntoContainerImage(ImVec4 color)
	{

		//TextureAtlas Coordinates for bar
		glm::vec2 topLeft = util::glNormalizeTextureCoords({ 66,67 }, { 512, 256 });
		glm::vec2 bottomRight = util::glNormalizeTextureCoords({ 129,128 }, { 512, 256 });

		if (GameConfig::instance().rendererType() == RendererType::OPENGL) {

			auto openGlTexture = TextureManager::instance().getTextureAtlas("textureAtlas_ImGui");
			GLuint64 textureAtlasId = static_cast<OpenGLTexture*>(openGlTexture.get())->textureId;
			ImGui::Image((void*)textureAtlasId, ImVec2(32, 32), ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color);
		}
		else {

			std::shared_ptr<Texture> texture = TextureManager::instance().getTextureAtlas("textureAtlas_ImGui");
			SDL_Texture* sdlTexture = std::static_pointer_cast<SDLTexture>(texture).get()->sdlTexture;
			ImGui::Image((void*)(SDL_Texture*)sdlTexture, ImVec2(32, 32), ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color);
		}

	}

	void _buildPuzzleRow(GameObject* puzzleObject)
	{
		static int buttonSeq{};

		const auto& puzzleComponent = puzzleObject->getComponent<PuzzleComponent>(ComponentTypes::PUZZLE_COMPONENT);

		//Clue text
		ImGui::PushStyleColor(ImGuiCol_Text, util::SDLColorToImVec4(Colors::CANDLE_LIGHT));
		ImGui::TextWrapped(puzzleComponent->puzzle->clue().c_str());
		ImGui::PopStyleColor();
		ImGui::NewLine();

		//Loop through all puzzles and display the status of the pieces
		for (auto piece : puzzleComponent->puzzle->pieces()) {

			ImGui::SameLine();

			if (piece == false) {

				ImGui::displayPuzzlePieceImage(true, util::SDLColorToImVec4(Colors::GREY));

			}
			else {
				ImGui::displayPuzzlePieceImage(false, util::SDLColorToImVec4(Colors::EMERALD));
			}

		}

	}
}
