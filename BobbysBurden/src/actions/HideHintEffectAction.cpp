#include "HideHintEffectAction.h"
#include "../components/BBInterfaceComponent.h"


void HideHintEffectAction::perform(GameObject* gameObject)
{

	auto cursor = TextureManager::instance().getMouseCursor("CURSOR_ARROW");
	SceneManager::instance().setMouseCursor(cursor);

}
