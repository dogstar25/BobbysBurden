#pragma once

#include "MobyDick.h"
#include "GameConstants.h"


class BBGameStateManager : public GameStateManager
{
public:
	BBGameStateManager();
	
	virtual void saveGame() override;
	void save(Json::Value gameData) override;

	virtual void loadGame() override;
	Json::Value getSaveData() override;
	virtual void loadGamePrimerFile() override;

	virtual void _applyDataToGame(Json::Value) override;
	virtual void _buildSaveGameData(Json::Value& saveGameData) override;

private:

	void _applyStates(std::shared_ptr<GameObject> gameObject, Json::Value states);
	void _applyInventory(std::shared_ptr<GameObject> gameObject, Json::Value inventory);
	void _applyPuzzle(std::shared_ptr<GameObject> gameObject, Json::Value puzzle);
	void _applyTransform(std::shared_ptr<GameObject> gameObject, Json::Value transform);


	void _buildTransformSaveData(GameObject*, Json::Value &saveGameObjectJSON);
	void _buildStateSaveData(GameObject* ,Json::Value& saveGameObjectJSON);
	void _buildInventorySaveData(GameObject* ,Json::Value& saveGameObjectJSON);
	void _buildPuzzleSaveData(GameObject* , Json::Value& saveGameObjectJSON);

};

																																																																																																																	