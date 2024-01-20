#include "OilBedKnobPuzzle.h"


OilBedKnobPuzzle::OilBedKnobPuzzle(std::string name, std::string clue, int pieceCount)
	:Puzzle(name, clue, pieceCount)
{


}

bool OilBedKnobPuzzle::isPuzzlePieceApplicable(GameObject* puzzlePieceObject)
{

	bool isApplicable = false;

	//Piece 1
	if (puzzlePieceObject->type() == "OIL_CAN") {

		isApplicable = true;
	}

	return isApplicable;

}

void OilBedKnobPuzzle::applyPuzzlePiece(GameObject* puzzleObject, GameObject* puzzlePieceObject)
{

	//Piece 1
	if (puzzlePieceObject->type() == "OIL_CAN") {

		m_pieces[0] = true;

	}

	//Create an unlock image to indicated the puzzle piece application worked
	auto position = puzzleObject->getCenterPosition();
	auto mapPosition = util::pixelToTileLocation(position.x, position.y);

	const auto& unlockObject = puzzlePieceObject->parentScene()->
		addGameObject("UNLOCK_ICON", GameLayer::FOREGROUND_4, (float)mapPosition.x, (float)mapPosition.y, (float)0);


 }
