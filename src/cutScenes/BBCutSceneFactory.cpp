#include "BBCutSceneFactory.h"
#include "BBCutSceneCaught.h"


std::shared_ptr<CutScene> BBCutSceneFactory::create(std::string cutSceneType)
{
	std::shared_ptr<CutScene> cutScene;

	if (cutSceneType == "BBCutSceneCaught") {

		cutScene = std::make_shared<BBCutSceneCaught>();

	}
	else {

		cutScene = CutSceneFactory::create(cutSceneType);

	}

	return cutScene;
}
