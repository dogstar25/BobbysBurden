#include "ClownPicturePuzzle.h"


ClownPicturePuzzle::ClownPicturePuzzle(std::string name, std::string clue, int pieceCount, GameObject* parent)
	:Puzzle(name, clue, pieceCount, parent)
{


}

bool ClownPicturePuzzle::isPuzzlePieceApplicable(GameObject* puzzlePieceObject)
{

	bool isApplicable = false;

	//Piece 1
	if (puzzlePieceObject->type() == "PAPER_BALLOON") {

		isApplicable = true;
	}

	return isApplicable;

}

void ClownPicturePuzzle::applyPuzzlePiece(GameObject* puzzleObject, GameObject* puzzlePieceObject)
{

	if (hasBeenSolved() == false) {

		//Piece 1
		if (puzzlePieceObject->type() == "PAPER_BALLOON") {

			m_pieces[0] = true;

		}

		//set the state to solved
		const auto& stateComponent = puzzleObject->getComponent<StateComponent>(ComponentTypes::STATE_COMPONENT);
		stateComponent->addState(GameObjectState::SOLVED);

		//Create an unlock image to indicated the puzzle piece application worked
		auto position = puzzleObject->getCenterPosition();
		auto mapPosition = util::pixelToTileLocation(position.x, position.y);

		const auto& unlockObject = puzzlePieceObject->parentScene()->
			addGameObject("UNLOCK_ICON", nullptr, GameLayer::FOREGROUND_4, (float)mapPosition.x - 1, (float)mapPosition.y, (float)0);

		unlockObject->setSize({ 32.0, 32.0 });

		puzzlePieceObject->setRemoveFromWorld(true);

	}
 }
