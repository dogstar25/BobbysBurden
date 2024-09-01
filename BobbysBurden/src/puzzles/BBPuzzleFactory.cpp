#include "BBPuzzleFactory.h"
#include "OilBedKnobPuzzle.h"
#include "ClownPicturePuzzle.h"
#include "MermaidMantlePuzzle.h"
#include "KillSpiderPuzzle.h"
#include "IndianStatuePuzzle.h"
#include "SkullPuzzle.h"



std::shared_ptr<Puzzle> BBPuzzleFactory::create(Json::Value puzzleJSON)
{
	std::shared_ptr<Puzzle> puzzle;

	std::string name = puzzleJSON["name"].asString();
	std::string clue = puzzleJSON["clue"].asString();
	int puzzlePieces = puzzleJSON["pieces"].asInt();
	std::string puzzleType = puzzleJSON["puzzleType"].asString();

	if (puzzleType == "OilBedKnobPuzzle") {

		puzzle = std::make_shared<OilBedKnobPuzzle>(name, clue, puzzlePieces);
	}
	else if (puzzleType == "ClownPicturePuzzle") {

		puzzle = std::make_shared<ClownPicturePuzzle>(name, clue, puzzlePieces);
	}
	else if (puzzleType == "MermaidMantlePuzzle") {

		puzzle = std::make_shared<MermaidMantlePuzzle>(name, clue, puzzlePieces);
	}
	else if (puzzleType == "KillSpiderPuzzle") {

		puzzle = std::make_shared<KillSpiderPuzzle>(name, clue, puzzlePieces);
	}
	else if (puzzleType == "IndianStatuePuzzle") {

		puzzle = std::make_shared<IndianStatuePuzzle>(name, clue, puzzlePieces);
	}
	else if (puzzleType == "SkullPuzzle") {

		puzzle = std::make_shared<SkullPuzzle>(name, clue, puzzlePieces);
	}

	else {

		puzzle = PuzzleFactory::create(puzzleJSON);
	}

	return puzzle;

}

