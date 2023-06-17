#include "OilBedKnobPuzzle.h"

bool OilBedKnobPuzzle::hasBeenSolved()
{
	return false;
}

bool OilBedKnobPuzzle::isPuzzlePieceApplicable(GameObject* puzzlePieceObject)
{

	if (m_pieces.find(puzzlePieceObject->name()) != m_pieces.end()) {
		return true;
	}

}

void OilBedKnobPuzzle::applyPuzzlePiece(std::string puzzlePieceId)
{
	Puzzle::applyPuzzlePiece(puzzlePieceId);


	auto iter = m_pieces.find(puzzlePieceId);
	iter->second.isSolved = true;

	//execute the keys "USE" action
	//which will play key unlock sound and animate the key

	//Do other stuff



}
