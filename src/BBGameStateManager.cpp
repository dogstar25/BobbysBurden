#include "BBGameStateManager.h"


extern std::unique_ptr<Game> game;

BBGameStateManager::BBGameStateManager()
	: GameStateManager()
{

	m_beginPrimerFilename = "BeginGamePrimerFile.json";

}

void BBGameStateManager::loadGamePrimerFile()
{

	//Get Json from the primer file
	std::string primerfilename = "config/" + m_beginPrimerFilename;
	auto primerFileReadResult = mobydick::ResourceManager::getJSON(primerfilename);
	if(!primerFileReadResult) {

		SDL_Log("Error reading in data from primer file %s", primerfilename.c_str());
		return;

	}

	//Save json to the save data file
	auto primerFileSaveResult = mobydick::ResourceManager::saveUserPathDataJSON(primerFileReadResult.value(), primerfilename);
	if (!primerFileSaveResult) {

		SDL_Log("Error saving data to primer file %s", primerfilename.c_str());
		abort();

	}

	_applyDataToGame(primerFileReadResult.value());

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

	//Read json to the save data file
	auto getSaveDataResult = mobydick::ResourceManager::getUserPathDataJSON(GAMEOBJECT_STATE_FILENAME);
	if (!getSaveDataResult) {

		SDL_Log("Error reading save game data %s", GAMEOBJECT_STATE_FILENAME);
		abort();

	}

	Json::Value loadedGameData = getSaveDataResult.value();

	return loadedGameData;

}

void BBGameStateManager::save(Json::Value saveGamaDataJSON)
{

	//save json to the save data file
	auto saveDataResult = mobydick::ResourceManager::saveUserPathDataJSON(saveGamaDataJSON, GAMEOBJECT_STATE_FILENAME.c_str());
	if (!saveDataResult) {

		SDL_Log("Error reading save game data %s", GAMEOBJECT_STATE_FILENAME);
		abort();

	}

	return;

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

	for (int i = 0; i < stateComponent->getStateBitSet().size(); ++i) {

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


