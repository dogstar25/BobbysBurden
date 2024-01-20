#include "ShowHintEffectAction.h"
#include "../components/BBInterfaceComponent.h"


void ShowHintEffectAction::perform(GameObject* gameObject)
{

	auto cursor = TextureManager::instance().getMouseCursor("CURSOR_ARROW_QUESTION");
	SceneManager::instance().setMouseCursor(cursor);
}
