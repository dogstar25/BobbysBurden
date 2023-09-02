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
			
				mainHudHolderChildren->removeChild(inventoryComponent->getDisplayBackdropObject().value()->id());

		}

		//call standard hide logic - has to be after removeing child form hud because the id gets wipes out here
		inventoryComponent->hideInventory();

	}
	else {
		const auto& mainHudHolder = playerObject->parentScene()->getFirstGameObjectByType("MAIN_HUD_HOLDER");
		if (mainHudHolder.has_value()) {
			inventoryComponent->showInventory(mainHudHolder.value().get());
		}
	}


}

