#pragma once
#include "MobyDick.h"

class KillSpiderPuzzle : public Puzzle
{
public:
	KillSpiderPuzzle() = default;
	KillSpiderPuzzle(std::string name, std::string clue, int pieceCount, GameObject* parent);

	virtual bool isPuzzlePieceApplicable(GameObject* puzzlePieceObject) override;
	virtual void applyPuzzlePiece(GameObject* puzzleObject, GameObject* puzzlePieceObject) override;
private:

};

