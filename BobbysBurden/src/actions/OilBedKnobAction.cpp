#include "OilBedKnobAction.h"
#include "../GameConstants.h"

void OilBedKnobAction::perform(GameObject* gameObject, GameObject* gameObject2)
{

	std::cout << "Oiled the bedknob!" << std::endl;

}

bool OilBedKnobAction::isApplicable(GameObject* gameObject, GameObject* gameObject2)
{

	return true;
}