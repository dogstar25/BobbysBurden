#pragma once
#include "MobyDick.h"

class MermaidMantlePuzzle : public Puzzle
{
public:
	MermaidMantlePuzzle() = default;
	MermaidMantlePuzzle(std::string name, std::string clue, int pieceCount);

	virtual bool isPuzzlePieceApplicable(GameObject* puzzlePieceObject) override;
	virtual void applyPuzzlePiece(GameObject* puzzleObject, GameObject* puzzlePieceObject) override;
private:

};

