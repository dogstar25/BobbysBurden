#include "ToggleBobbyInventory.h"
#include "../GameConstants.h"

extern std::unique_ptr<Game> game;

void ToggleBobbyInventory::perform(GameObject* playerObject)
{

	const auto& inventoryComponent = playerObject->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);

	if (inventoryComponent->isOpen()) {
		
		//Get the Main HUD Holder and remove the bobby inventory object
		const auto& mainHudHolder = playerObject->parentScene()->getFirstGameObjectByType("MAIN_HUD_HOLDER");
		if (mainHudHolder.has_value()) {
			const auto& mainHudHolderChildren = mainHudHolder.value()->getComponent<ChildrenComponent>(ComponentTypes::CHILDREN_COMPONENT);
			
				mainHudHolderChildren->removeChild(inventoryComponent->getDisplayObject().value().lock()->id());

		}

		//call standard hide logic - has to be after removeing child form hud because the id gets wipes out here
		inventoryComponent->setOpen(false);
		inventoryComponent->hideInventory();

	}
	else {
		const auto& mainHudHolder = playerObject->parentScene()->getFirstGameObjectByType("MAIN_HUD_HOLDER");

		if (mainHudHolder.has_value()) {

			const auto& mainHudHolderChildren = mainHudHolder.value()->getComponent<ChildrenComponent>(ComponentTypes::CHILDREN_COMPONENT);

			mainHudHolderChildren->addStepChild(inventoryComponent->getDisplayObject().value().lock(), PositionAlignment::CENTER, false);

			inventoryComponent->setOpen(true);
			inventoryComponent->showInventory();

		}
	}


}

