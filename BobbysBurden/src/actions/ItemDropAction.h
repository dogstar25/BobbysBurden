#pragma once
#include "MobyDick.h"

class ItemDropAction : public Action
{

public:
	void perform(GameObject* gameObject) override;

protected:
	void _handleDropOnInventory(GameObject* gameObject);
	void _handleDropOnPuzzle(GameObject* puzzleGameObject, GameObject* droppedGameObject);


};

