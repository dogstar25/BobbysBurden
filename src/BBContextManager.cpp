#include "BBContextManager.h"
#include "GameConstants.h"


extern std::unique_ptr<Game> game;


void BBContextManager::loadSettings()
{

	std::string settingFilename = game->gameStateMananger()->getGamePath() + GAME_SETTINGS_FILENAME;

	//If the settings file has never been created then create it and default the values
	if (util::fileExists(settingFilename) == false) {
		
		setMouseSensitivity(50);
		setSoundVolume(50);
		saveSettings();
		return;
	}

	std::ifstream m_gameFile(game->gameStateMananger()->getGamePath() + GAME_SETTINGS_FILENAME, std::ofstream::in);

	if (!m_gameFile.is_open()) {
		std::cerr << "Error opening game settings file" << std::endl;
		assert(m_gameFile && "Error opening game settings file");
	}

	Json::Value loadedGameData;
	m_gameFile >> loadedGameData;

	if (!m_gameFile) {
		std::cerr << "Error parsing game settings file" << std::endl;
		assert(m_gameFile && "Error parsing game settings file");
	}

	m_gameFile.close();

	//Apply settinmgs data
	if (loadedGameData["settings"].isMember("mouseSensitivity")) {

		setMouseSensitivity(loadedGameData["settings"]["mouseSensitivity"].asInt());
	}

	if (loadedGameData["settings"].isMember("soundVolume")) {

		setSoundVolume(loadedGameData["settings"]["soundVolume"].asInt());
	}

}

bool BBContextManager::saveSettings()
{

	//Get whats currently there
	Json::Value saveData;

	//Replace the settings items
	saveData["settings"]["soundVolume"] = getSoundVolume();
	saveData["settings"]["mouseSensitivity"] = getMouseSensitivity();

	std::ofstream m_gameFile(game->gameStateMananger()->getGamePath() + GAME_SETTINGS_FILENAME, std::ofstream::out);

	Json::StreamWriterBuilder writer;
	std::string saveGameData = Json::writeString(writer, saveData);

	m_gameFile << saveGameData;
	m_gameFile.close();

	assert(m_gameFile && "Error writing game file");

	return true;
}


