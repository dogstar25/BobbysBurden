#include "BBPuzzleFactory.h"
#include "OilBedKnobPuzzle.h"



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
	else {

		puzzle = PuzzleFactory::create(puzzleType);
	}

	return puzzle;

}

