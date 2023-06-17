#include "HideUnderBedAction.h"
#include "../GameConstants.h"

void HideUnderBedAction::perform(GameObject* gameObject, GameObject* gameObject2)
{

	std::cout << "Went to bed!" << std::endl;

}

bool HideUnderBedAction::isApplicable(GameObject* gameObject, GameObject* gameObject2)
{
	return false;
}