#include "DisableProximityHintAction.h"
#include "../components/BBInterfaceComponent.h"


void DisableProximityHintAction::perform()
{

	const auto& childrenComponent =
		m_parent->getComponent<ChildrenComponent>(ComponentTypes::CHILDREN_COMPONENT);
	auto children = childrenComponent->getChildrenByType("PUZZLE_HINT_SENSOR_BOX");

	if (children.empty() == false) {

		childrenComponent->removeChildrenByType("PUZZLE_HINT_SENSOR_BOX");
		auto position = m_parent->getCenterPosition();
		auto mapPosition = util::pixelToTileLocation(position.x, position.y);

		m_parent->addLitHighlight({ 128,128 });
	}



}
