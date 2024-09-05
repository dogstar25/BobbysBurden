#include "BBPuzzleFactory.h"
#include "OilBedKnobPuzzle.h"
#include "ClownPicturePuzzle.h"
#include "MermaidMantlePuzzle.h"
#include "KillSpiderPuzzle.h"
#include "IndianStatuePuzzle.h"
#include "SkullPuzzle.h"



std::shared_ptr<Puzzle> BBPuzzleFactory::create(Json::Value puzzleJSON, GameObject* parent)
{
	std::shared_ptr<Puzzle> puzzle;

	std::string name = puzzleJSON["name"].asString();
	std::string clue = puzzleJSON["clue"].asString();
	int puzzlePieces = puzzleJSON["pieces"].asInt();
	std::string puzzleType = puzzleJSON["puzzleType"].asString();

	if (puzzleType == "OilBedKnobPuzzle") {

		puzzle = std::make_shared<OilBedKnobPuzzle>(name, clue, puzzlePieces, parent);
	}
	else if (puzzleType == "ClownPicturePuzzle") {

		puzzle = std::make_shared<ClownPicturePuzzle>(name, clue, puzzlePieces, parent);
	}
	else if (puzzleType == "MermaidMantlePuzzle") {

		puzzle = std::make_shared<MermaidMantlePuzzle>(name, clue, puzzlePieces, parent);
	}
	else if (puzzleType == "KillSpiderPuzzle") {

		puzzle = std::make_shared<KillSpiderPuzzle>(name, clue, puzzlePieces, parent);
	}
	else if (puzzleType == "IndianStatuePuzzle") {

		puzzle = std::make_shared<IndianStatuePuzzle>(name, clue, puzzlePieces, parent);
	}
	else if (puzzleType == "SkullPuzzle") {

		puzzle = std::make_shared<SkullPuzzle>(name, clue, puzzlePieces, parent);
	}

	else {

		puzzle = PuzzleFactory::create(puzzleJSON, parent);
	}

	return puzzle;

}

