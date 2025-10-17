#pragma once
#include "MobyDick.h"

class OilBedKnobPuzzle : public Puzzle
{
public:
	OilBedKnobPuzzle() = default;
	OilBedKnobPuzzle(std::string name, std::string clue, int pieceCount, GameObject* parent);

	virtual bool isPuzzlePieceApplicable(GameObject* puzzlePieceObject) override;
	virtual void applyPuzzlePiece(GameObject* puzzleObject, GameObject* puzzlePieceObject) override;
private:

};

