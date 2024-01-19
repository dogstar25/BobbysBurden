#pragma once
#include <MobyDick.h>

class BBPuzzleFactory : public PuzzleFactory
{
public:
	BBPuzzleFactory() = default;

	virtual std::shared_ptr<Puzzle> create(Json::Value pauzzleJSON) override;

private:

};

