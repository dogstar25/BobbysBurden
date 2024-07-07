#pragma once
#include "MobyDick.h"

class BBCutSceneFactory : public CutSceneFactory
{
public:
	
	virtual std::shared_ptr<CutScene> create(std::string cutSceneType) override;

private:

};
