#include "PlayCutSceneAction.h"
#include "../GameConstants.h"

void PlayCutSceneAction::perform(GameObject* gameObject)
{

	SDL_Event event;

	//Get the cut scene name from properties
	
	std::string cutScene = util::getJsonProperty("cutSceneName", m_properties).asString();


	//Create the event that will trigger the end of the scene to the sceneManager
	util::sendSceneEvent(SCENE_ACTION_DIRECT, cutScene);

}

