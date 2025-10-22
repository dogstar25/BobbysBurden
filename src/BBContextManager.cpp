#include "BBContextManager.h"
#include "GameConstants.h"


extern std::unique_ptr<Game> game;


void BBContextManager::loadSettings()
{

	auto settingsResult = mobydick::ResourceManager::getUserPathDataJSON(GAME_SETTINGS_FILENAME);
	if (!settingsResult) {

		SDL_Log("%s", "loadSettings: Error opening GAME_SETTINGS_FILENAME");
		abort();

	}

	Json::Value settingsJSON = settingsResult.value();

	//If the settings file has never been created then create it and default the values
	if (settingsJSON.empty()) {
		
		setMouseSensitivity(50);
		setSoundVolume(50);
		saveSettings();
		return;
	}

	//Apply settinmgs data
	if (settingsJSON["settings"].isMember("mouseSensitivity")) {

		setMouseSensitivity(settingsJSON["settings"]["mouseSensitivity"].asInt());
	}

	if (settingsJSON["settings"].isMember("soundVolume")) {

		setSoundVolume(settingsJSON["settings"]["soundVolume"].asInt());
	}

}

bool BBContextManager::saveSettings()
{

	//Get whats currently there
	Json::Value saveData;

	//Replace the settings items
	saveData["settings"]["soundVolume"] = getSoundVolume();
	saveData["settings"]["mouseSensitivity"] = getMouseSensitivity();

	auto settingsResult = mobydick::ResourceManager::saveUserPathDataJSON(saveData, GAME_SETTINGS_FILENAME);
	if (!settingsResult) {

		SDL_Log("loadSettings: Error saving %s", GAME_SETTINGS_FILENAME.c_str());
		abort();

	}

	return true;
}


