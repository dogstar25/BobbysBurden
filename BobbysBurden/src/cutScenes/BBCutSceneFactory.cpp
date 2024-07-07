#include "BBCutSceneFactory.h"
#include "CutSceneClownArtMove.h"


std::shared_ptr<CutScene> BBCutSceneFactory::create(std::string cutSceneType)
{
	std::shared_ptr<CutScene> cutScene;

	if (cutSceneType == "CutSceneClownArtMove") {

		cutScene = std::make_shared<CutSceneClownArtMove>();
	}
	else {

		cutScene = CutSceneFactory::create(cutSceneType);
	}

	return cutScene;
}
