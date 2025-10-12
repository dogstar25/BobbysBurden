#include "ItemDragTreatmentAction.h"

extern std::unique_ptr<Game> game;

void ItemDragTreatmentAction::perform()
{

	//If the object being dragged is out of Bobby's reach range, then apply a red overlay
	if (m_parent->isTouchingByTrait(TraitTag::player) == false ) {

		const auto& renderComponent = m_parent->getComponent<RenderComponent>(ComponentTypes::RENDER_COMPONENT);
		renderComponent->applyDisplayOverlay(displayOverlays::tint_RED1);
	}
	else {
		const auto& renderComponent = m_parent->getComponent<RenderComponent>(ComponentTypes::RENDER_COMPONENT);
		renderComponent->removeDisplayOverlay();

	}


}
