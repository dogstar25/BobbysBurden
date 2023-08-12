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
			const auto& mainHudHolderCildren = mainHudHolder.value()->getComponent<ChildrenComponent>(ComponentTypes::CHILDREN_COMPONENT);
			
			//remove child
			if (inventoryComponent->getDisplayInventoryObjectId()) {
				std::string displayObjectId = inventoryComponent->getDisplayInventoryObjectId().value();
				mainHudHolderCildren->removeChild(displayObjectId);
			}

		}

		//call standard hide logic - has to be after removeing child form hud because the id gets wipes out here
		inventoryComponent->hideInventory();

	}
	else {
		
		inventoryComponent->showInventory("MAIN_HUD_HOLDER");
	}


}

