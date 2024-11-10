#include "../GameConstants.h"
#include "KillSpiderPuzzle.h"



KillSpiderPuzzle::KillSpiderPuzzle(std::string name, std::string clue, int pieceCount, GameObject* parent)
	:Puzzle(name, clue, pieceCount, parent)
{


}

bool KillSpiderPuzzle::isPuzzlePieceApplicable(GameObject* puzzlePieceObject)
{

	bool isApplicable = false;

	//Piece 1
	if (puzzlePieceObject->type() == "BUGSPRAY") {

		isApplicable = true;
	}

	return isApplicable;

}

void KillSpiderPuzzle::applyPuzzlePiece(GameObject* puzzleObject, GameObject* puzzlePieceObject)
{

	if (hasBeenSolved() == false) {

		//Piece 1
		if (puzzlePieceObject->type() == "BUGSPRAY") {

			m_pieces[0] = true;

		}

		//Create an unlock image to indicated the puzzle piece application worked
		auto position = puzzleObject->getCenterPosition();
		auto mapPosition = util::pixelToTileLocation(position.x, position.y);

		const auto& unlockObject = puzzlePieceObject->parentScene()->
			addGameObject("UNLOCK_ICON", nullptr, GameLayer::FOREGROUND_4, (float)mapPosition.x - 1, (float)mapPosition.y, (float)0);

		unlockObject->setSize({ 32.0, 32.0 });

		puzzlePieceObject->setRemoveFromWorld(true);

		//Hide the spider puzzle
		puzzleObject->setRemoveFromWorld(true);

		//Spawn a dead spider
		auto puzzlePosition = puzzleObject->parent().value()->getCenterPosition();

		puzzlePosition.x += 0;
		puzzlePosition.y += 0;

		auto newPosition = puzzlePosition;
		auto tilePosition = util::pixelToTileLocation(newPosition.x, newPosition.y);
		tilePosition.x -= 6;
		tilePosition.y += 1;

		puzzleObject->parentScene()->addGameObject("DEAD_SPIDER", nullptr, GameLayer::BACKGROUND_3, 
			static_cast<float>(tilePosition.x), static_cast<float>(tilePosition.y));


		//Get the scary object and execute the removeScare action from it
		const auto& childrenComponent = puzzleObject->getComponent<ChildrenComponent>(ComponentTypes::CHILDREN_COMPONENT);
		const auto& scaryObject = childrenComponent->getFirstChildByType("SCARY_OBJECT");
		const auto& scaryObjectActionComponent = scaryObject.value()->getComponent<ActionComponent>(ComponentTypes::ACTION_COMPONENT);
		const auto removeScareAction = scaryObjectActionComponent->getAction(Actions::REMOVE_SCARE);
		removeScareAction->perform();

		//disable the puzzle so that it is no long active
		puzzleObject->disableUpdate();

	}
 }
