#include "HideAction.h"
#include "../GameConstants.h"

void HideAction::perform(GameObject* gameObject)
{

	std::cout << "Bobby Hid in the " << gameObject->name() << "!" << std::endl;

}

