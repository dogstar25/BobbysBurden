#include "TwistBedKnobAction.h"
#include "../GameConstants.h"

void TwistBedKnobAction::perform(GameObject* gameObject, GameObject* gameObject2)
{

	std::cout << "Twisted the bedknob!" << std::endl;

}

bool TwistBedKnobAction::isApplicable(GameObject* gameObject, GameObject* gameObject2)
{

	return true;
}