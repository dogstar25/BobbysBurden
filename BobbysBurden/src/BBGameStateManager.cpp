#include "BBGameStateManager.h"


extern std::unique_ptr<Game> game;

BBGameStateManager::BBGameStateManager()
	: GameStateManager()
{

	// Adjust path to fit this game
	std::string path = getGamePath();
	path += "\\BobbysGhostAdventure";
	setGamePath(path);

	m_beginPrimerFilename = "BeginGamePrimerFile.json";

	if (!std::filesystem::is_directory(m_saveGamePath) || !std::filesystem::exists(m_saveGamePath)) {
		if (std::filesystem::create_directory(m_saveGamePath) == false) {
			assert(true && "Error creating save game directory!");
		}
	}

}

void BBGameStateManager::loadGamePrimerFile()
{

	std::string texturefilename = "assets/config/" + m_beginPrimerFilename;
	std::ifstream fin(texturefilename);

	Json::CharReaderBuilder readerBuilder;
	std::string errs;
	Json::Value loadedPrimerData;

	bool parsingSuccessful = Json::parseFromStream(readerBuilder, fin, &loadedPrimerData, &errs);

	fin.close();

	save(loadedPrimerData);

	_applyDataToGame(loadedPrimerData);

}

void BBGameStateManager::_applyDataToGame(Json::Value gameData)
{

	//Apply gameObject Inventory
	for (auto& jsonItr : gameData["gameObjects"]) {

		std::string name = jsonItr["gameObjectName"].asString();
		std::string type = jsonItr["gameObjectType"].asString();

		const auto& gameObjects = SceneManager::instance().currentScene().getGameObjectsByName(name);

		//There could be more than one gameObject with the same name like partner doors
		//should be rare though
		for (const auto& gameObject : gameObjects) {

			//Also match on gameObject Type because there are a few scenarios where we have the same name
			//Like partner doors
			if (type == gameObject->type()) {

				if (jsonItr.isMember("state")) {

					_applyStates(gameObject, jsonItr["state"]);

				}

				if (jsonItr.isMember("inventory")) {

					_applyInventory(gameObject, jsonItr["inventory"]);

				}

				if (jsonItr.isMember("puzzle")) {

					_applyPuzzle(gameObject, jsonItr["puzzle"]);

				}

				if (jsonItr.isMember("transform")) {

					_applyTransform(gameObject, jsonItr["transform"]);

				}

			}
		}

	}

}

void BBGameStateManager::_buildSaveGameData(Json::Value& saveGameData)
{
	Json::Value saveGameObjectData{};
	const auto& gameObjects = SceneManager::instance().currentScene().getGameObjectLookup();


	auto it = gameObjects.begin();
	while (it != gameObjects.end()) {

		saveGameObjectData.clear();

		if (it->second.expired() == false && it->second.lock()->hasTrait(TraitTag::save_me)) {

			saveGameObjectData["gameObjectName"] = it->second.lock().get()->name();
			saveGameObjectData["gameObjectType"] = it->second.lock().get()->type();;

			_buildTransformSaveData(it->second.lock().get(), saveGameObjectData);

			if (it->second.lock()->hasComponent(ComponentTypes::STATE_COMPONENT)) {
				_buildStateSaveData(it->second.lock().get(), saveGameObjectData);
			}

			if (it->second.lock()->hasComponent(ComponentTypes::INVENTORY_COMPONENT)) {
				_buildInventorySaveData(it->second.lock().get(), saveGameObjectData);
			}

			if (it->second.lock()->hasComponent(ComponentTypes::PUZZLE_COMPONENT)) {
				_buildPuzzleSaveData(it->second.lock().get(), saveGameObjectData);
			}

			saveGameData["gameObjects"].append(saveGameObjectData);

		}
		
		++it;
	}

}


void BBGameStateManager::loadGame()
{

	Json::Value loadedGameData = getSaveData();

	_applyDataToGame(loadedGameData);

}

Json::Value BBGameStateManager::getSaveData()
{

	std::ifstream m_gameFile(m_saveGamePath + GAMEOBJECT_STATE_FILENAME, std::ofstream::in);

	if (!m_gameFile.is_open()) {
		std::cerr << "Error opening game file" << std::endl;
		return false;
	}

	Json::Value loadedGameData;
	m_gameFile >> loadedGameData;

	if (!m_gameFile) {
		std::cerr << "Error reading game file" << std::endl;
		return false;
	}

	m_gameFile.close();

	return loadedGameData;

}

void BBGameStateManager::save(Json::Value saveGamaDataJSON)
{

	// Convert the serialized Json::Value to a formatted text string
	Json::StreamWriterBuilder writer;
	//writer["indentation"] = "  ";  // or whatever indentation you prefer
	std::string saveGameData = Json::writeString(writer, saveGamaDataJSON);

	//write jsonString to output file
	std::ofstream m_gameFile(m_saveGamePath + GAMEOBJECT_STATE_FILENAME, std::ofstream::out);

	m_gameFile << saveGameData;
	m_gameFile.close();

	assert(m_gameFile && "Error writing game file");

}

void BBGameStateManager::saveGame()
{

	//Add to the saveGameData that was passed in
	Json::Value saveGamaDataJSON{};

	_buildSaveGameData(saveGamaDataJSON);

	save(saveGamaDataJSON);

}

void BBGameStateManager::_applyStates(std::shared_ptr<GameObject> gameObject, Json::Value states)
{

	const auto& stateComponent = gameObject->getComponent<StateComponent>(ComponentTypes::STATE_COMPONENT);

	stateComponent->clear();

	for (const auto& stateJSON: states) {

		auto state = (GameObjectState)game->enumMap()->toEnum(stateJSON.asString());

		stateComponent->addState(state);

	}

}

void BBGameStateManager::_applyTransform(std::shared_ptr<GameObject> gameObject, Json::Value transform)
{

	const auto& transformComponent = gameObject->getComponent<TransformComponent>(ComponentTypes::TRANSFORM_COMPONENT);

	SDL_FPoint location = {transform["x"].asFloat(), transform["y"].asFloat() };
	transformComponent->setPosition(location);


}


void BBGameStateManager::_applyPuzzle(std::shared_ptr<GameObject> gameObject, Json::Value puzzle)
{

	const auto& puzzleComponent = gameObject->getComponent<PuzzleComponent>(ComponentTypes::PUZZLE_COMPONENT);

	int index{};

	for (Json::Value puzzlePieceFlag : puzzle["pieces"]) {

		bool flag = puzzlePieceFlag.asBool();

		if (index < puzzleComponent->puzzle->pieces().size()){

			puzzleComponent->puzzle->setPiece(index, flag);
		}

		index++;

	}

}

void BBGameStateManager::_applyInventory(std::shared_ptr<GameObject> gameObject, Json::Value inventory)
{

	const auto& inventoryComponent = gameObject->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);

	inventoryComponent->clearInventory();

	for (Json::Value itemJSON : inventory) {

		inventoryComponent->addItem(itemJSON["type"].asString(), itemJSON["slot"].asInt());

	}

	inventoryComponent->refreshInventoryDisplay();

}

void BBGameStateManager::_buildTransformSaveData(GameObject* gameObject, Json::Value& saveGameObjectJSON)
{

	
	saveGameObjectJSON["transform"]["x"] = gameObject->getComponent<TransformComponent>(ComponentTypes::TRANSFORM_COMPONENT)->getCenterPosition().x;
	saveGameObjectJSON["transform"]["y"] = gameObject->getComponent<TransformComponent>(ComponentTypes::TRANSFORM_COMPONENT)->getCenterPosition().y;


}

void BBGameStateManager::_buildStateSaveData(GameObject* gameObject, Json::Value& saveGameObjectJSON)
{

	const auto& stateComponent = gameObject->getComponent<StateComponent>(ComponentTypes::STATE_COMPONENT);

	for (size_t i = 0; i < stateComponent->getStateBitSet().size(); ++i) {

		if (stateComponent->testState(static_cast<GameObjectState>(i))) {

			std::string name = game->enumMap()->findKeyWithValueHint(i, "GameObjectState::");

			saveGameObjectJSON["state"].append(name);

		}

	}

}

void BBGameStateManager::_buildInventorySaveData(GameObject* gameObject, Json::Value& saveGameObjectJSON)
{

	const auto& inventoryComponent = gameObject->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);

	int slot{};

	for (const auto& item : inventoryComponent->items()) {

		if (item.has_value()) {

			Json::Value itemJSON{};
			itemJSON["type"] = item.value()->type();
			itemJSON["slot"] = slot;

			saveGameObjectJSON["inventory"].append(itemJSON);

		}

		slot++;

	}
	



}

void BBGameStateManager::_buildPuzzleSaveData(GameObject* gameObject, Json::Value& saveGameObjectJSON)
{
	const auto& puzzleComponent = gameObject->getComponent<PuzzleComponent>(ComponentTypes::PUZZLE_COMPONENT);

	for (const auto piece : puzzleComponent->puzzle->pieces()) {

		saveGameObjectJSON["puzzle"]["pieces"].append((bool)piece);

	}


}


