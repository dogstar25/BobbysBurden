#pragma once
#include "MobyDick.h"

class ItemDropAction : public Action
{

public:
	ItemDropAction(Json::Value properties, GameObject* parent)
		:Action(properties, parent) {}

	void perform(GameObject* gameObject) override;

protected:
	void _handleDropOnInventory(GameObject* gameObject, GameObject* destinationInventoryObject);
	void _handleDropOnPuzzle(GameObject* puzzleGameObject, GameObject* droppedGameObject);


};

