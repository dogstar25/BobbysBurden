#include "BBPuzzleFactory.h"
#include "OilBedKnobPuzzle.h"



std::shared_ptr<Puzzle> BBPuzzleFactory::create(std::string puzzleType)
{
	std::shared_ptr<Puzzle> puzzle;

	if (puzzleType == "OilBedKnobPuzzle") {

		puzzle = std::make_shared<OilBedKnobPuzzle>();
	}
	else {

		puzzle = PuzzleFactory::create(puzzleType);
	}

	return puzzle;

}

