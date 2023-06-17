#pragma once
#include "MobyDick.h"

class OilBedKnobPuzzle : public Puzzle
{
public:
	OilBedKnobPuzzle() = default;
	virtual bool hasBeenSolved() override;
	virtual bool isPuzzlePieceApplicable(GameObject* puzzlePieceObject) override;
	virtual void applyPuzzlePiece(std::string puzzlePieceId) override;
private:

};

