#include "ToggleBobbyInventory.h"
#include "../GameConstants.h"

extern std::unique_ptr<Game> game;

void ToggleBobbyInventory::perform()
{

	const auto& inventoryComponent = m_parent->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);

	if (inventoryComponent->isOpen()) {
		
		//Get the Main HUD Holder and remove the bobby inventory object
		const auto& mainHudHolder = m_parent->parentScene()->getFirstGameObjectByType("MAIN_HUD_HOLDER");
		if (mainHudHolder.has_value()) {
			const auto& mainHudHolderChildren = mainHudHolder.value()->getComponent<ChildrenComponent>(ComponentTypes::CHILDREN_COMPONENT);
			
				mainHudHolderChildren->removeChild(inventoryComponent->getDisplayObject().value().lock()->id());

		}

		//call standard hide logic - has to be after removeing child form hud because the id gets wipes out here
		inventoryComponent->setOpen(false);
		inventoryComponent->hideInventory();

	}
	else {
		const auto& mainHudHolder = m_parent->parentScene()->getFirstGameObjectByType("MAIN_HUD_HOLDER");

		if (mainHudHolder.has_value()) {

			const auto& mainHudHolderChildren = mainHudHolder.value()->getComponent<ChildrenComponent>(ComponentTypes::CHILDREN_COMPONENT);

			mainHudHolderChildren->addStepChild(inventoryComponent->getDisplayObject().value().lock(), PositionAlignment::CENTER, false);

			inventoryComponent->setOpen(true);
			inventoryComponent->showInventory();

		}
	}


}

