#pragma once
#include "MobyDick.h"

class ClownPicturePuzzle : public Puzzle
{
public:
	ClownPicturePuzzle() = default;
	ClownPicturePuzzle(std::string name, std::string clue, int pieceCount, GameObject* parent);

	virtual bool isPuzzlePieceApplicable(GameObject* puzzlePieceObject) override;
	virtual void applyPuzzlePiece(GameObject* puzzleObject, GameObject* puzzlePieceObject) override;
private:

};

