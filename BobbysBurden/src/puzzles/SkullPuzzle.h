#pragma once
#include "MobyDick.h"

class SkullPuzzle : public Puzzle
{
public:
	SkullPuzzle() = default;
	SkullPuzzle(std::string name, std::string clue, int pieceCount);

	virtual bool isPuzzlePieceApplicable(GameObject* puzzlePieceObject) override;
	virtual void applyPuzzlePiece(GameObject* puzzleObject, GameObject* puzzlePieceObject) override;
private:

};

