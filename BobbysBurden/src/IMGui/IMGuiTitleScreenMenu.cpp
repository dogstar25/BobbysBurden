#include "IMGuiTitleScreenMenu.h"

#include "MobyDick.h"

#include "../BBContextManager.h"
#include "../GameConstants.h"
#include "../IMGui/BB_IMGuiUtil.h"
#include "../BBGameStateManager.h"


extern std::unique_ptr<Game> game;


IMGuiTitleScreenMenu::IMGuiTitleScreenMenu(std::string gameObjectType, b2Vec2 padding, ImVec4 backgroundColor, ImVec4 textColor,
	ImVec4 buttonColor, ImVec4 buttonHoverColor, ImVec4 buttonActiveColor, bool autoSize) :
	IMGuiItem(gameObjectType, padding, backgroundColor, textColor, buttonColor, buttonHoverColor, buttonActiveColor, autoSize)
{
	m_flags = ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize;

}

glm::vec2 IMGuiTitleScreenMenu::render()
{
	ImVec2 buttonSize{ ImGui::GameSettings::button1Size };
	glm::vec2 windowSize{};
	bool continueButtonDisabled{};

	const auto& renderComponent = parent()->getComponent<RenderComponent>(ComponentTypes::RENDER_COMPONENT);
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	setWindowProperties(parent());

	//Set Color
	ImGui::PushStyleColor(ImGuiCol_WindowBg, m_backgroundColor);

	ImGui::Begin(m_gameObjectType.c_str(), nullptr, m_flags);
	{

		ImGui::PushStyleColor(ImGuiCol_Text, m_textColor);
		ImGui::PushStyleColor(ImGuiCol_Button, m_buttonColor);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_buttonHoverColor);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_buttonActiveColor);

		//top window spacing
		ImGui::Spacing();

		//Continue Button - disable if the player hasnt yet started a game
		if (false) {
			continueButtonDisabled = true;
		}

		if(continueButtonDisabled){
			ImGui::BeginDisabled();
		}

		if (ImGui::Button("Continue", ImGui::GameSettings::button1Size)) {
			ImGui::continueGameLoad();
		}

		if (continueButtonDisabled) {
			ImGui::EndDisabled();
		}

		//spacing
		ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();

		if (ImGui::Button("New Game", ImGui::GameSettings::button1Size)) {
			ImGui::newGameLoad();
		}

		//spacing
		ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();

		//Settings Button
		if (ImGui::Button("Settings", ImGui::GameSettings::button1Size)) {
			ImGui::OpenPopup("SettingsModal");
		}

		if (ImGui::BeginPopupModal("SettingsModal", nullptr, m_SettingsModalflags)) {
			settingsModal();
		}

		//spacing
		ImGui::Spacing(); ImGui::Spacing();	ImGui::Spacing(); ImGui::Spacing();

		//Exit Button
		if (ImGui::Button("Exit Game", ImGui::GameSettings::button1Size)) {
			util::sendSceneEvent(SCENE_ACTION_QUIT);
		}

		//spacing
		ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();

		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();


		windowSize = { ImGui::GetWindowSize().x, ImGui::GetWindowSize().y };

	}

	ImGui::End();

	ImGui::PopStyleColor();

	return windowSize;

}



void IMGuiTitleScreenMenu::settingsModal()
{

	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetWindowPos(ImVec2{ center.x - m_settingsModalSize.x / 2, center.y - m_settingsModalSize.y / 2 });
	ImGui::SetWindowSize(m_settingsModalSize);

	//Button Style
	ImGui::PushStyleColor(ImGuiCol_Text, util::SDLColorToImVec4(Colors::WHITE));
	ImGui::PushStyleColor(ImGuiCol_Button, util::SDLColorToImVec4(Colors::BLUE));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_buttonHoverColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_buttonActiveColor);

	ImGui::SameLine(24);
	ImGui::BeginGroup();

	//Spacing
	ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();

	// Mouse sensitivity setting slider
	ImGui::Text("Mouse Sensitivity");
	static int mouseSensitivity = game->contextMananger()->getMouseSensitivityForGui();
	ImGui::SliderInt("##mouseSensitivity", &mouseSensitivity, 0, 100);

	//Spacing
	ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();

	// Sounds Level setting slider
	static int soundvolume = game->contextMananger()->getSoundVolumeForGui();
	ImGui::Text("Sound Volume");
	ImGui::SliderInt("##soundvolume", &soundvolume, 0, 100);

	//Spacing
	ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();

	//Buttons
	if (ImGui::Button("Ok", ImGui::GameSettings::button1Size)) {
		apply(mouseSensitivity, soundvolume);
		ImGui::CloseCurrentPopup();
		//ImGui::sendSceneExitEvent();
	}

	ImGui::SameLine(156);
	if (ImGui::Button("Cancel", ImGui::GameSettings::button1Size)) {
		ImGui::CloseCurrentPopup();
		//ImGui::sendSceneExitEvent();
	}
	ImGui::EndGroup();


	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();


	if (ImGui::IsKeyPressed(ImGuiKey_G)) {
		std::cout << "Settings Modal Key Pressed" << "\n";
	}

	ImGui::EndPopup();

}

void IMGuiTitleScreenMenu::apply(int mouseSensitivity, int soundVolume)
{

	game->contextMananger()->setMouseSensitivity(mouseSensitivity);
	game->contextMananger()->setSoundVolume(soundVolume);

	game->contextMananger()->saveSettings();

}



