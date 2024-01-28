#include "DisableProximityHintAction.h"
#include "../components/BBInterfaceComponent.h"


void DisableProximityHintAction::perform(GameObject* gameObject)
{

	const auto& childrenComponent =
		gameObject->getComponent<ChildrenComponent>(ComponentTypes::CHILDREN_COMPONENT);
	auto children = childrenComponent->getChildrenByType("PUZZLE_HINT_SENSOR_BOX");

	if (children.empty() == false) {

		childrenComponent->removeChildrenByType("PUZZLE_HINT_SENSOR_BOX");
		auto position = gameObject->getCenterPosition();
		auto mapPosition = util::pixelToTileLocation(position.x, position.y);

		gameObject->addLitHighlight({ 128,128 });
	}



}
