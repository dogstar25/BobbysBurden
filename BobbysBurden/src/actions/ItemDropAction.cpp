#include "ItemDropAction.h"

extern std::unique_ptr<Game> game;

void ItemDropAction::perform(GameObject* gameObject)
{

	//If there was a overlay added to the dragging somewhere then make sure its clear
	const auto& renderComponent = gameObject->getComponent<RenderComponent>(ComponentTypes::RENDER_COMPONENT);
	renderComponent->removeDisplayOverlay();

	//Did we drop onto an inventory holding gameObject
	if (gameObject->isTouchingByTrait(TraitTag::inventory)) {

		//Get reference to this dropped objects' inventory component
		const auto& droppedObjectParent = gameObject->parent();
		const auto& sourceInventoryObject = droppedObjectParent.value()->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);
		
		const auto& touchingInventoryObject = gameObject->getFirstTouchingByTrait(TraitTag::inventory).value().lock();

		if (touchingInventoryObject->hasComponent(ComponentTypes::GRID_DISPLAY_COMPONENT)) {

			//This is a grid display object so get its grid display component
			const auto& gridDisplayComponent = touchingInventoryObject->getComponent<GridDisplayComponent>(ComponentTypes::GRID_DISPLAY_COMPONENT);

			//Get the grid slot that we dropped this object on. if it wasnt close enough to any then we
			//wont move the object
			auto slot = gridDisplayComponent->getClosestSlot(gameObject->getCenterPosition());
			if (slot.has_value()) {

				//This grid display gameObject should have a parent that is the inventory holding object itself
				//So get a reference to it and its inventory component
				const auto& destinationInventoryObject = touchingInventoryObject->parent().value();

				//Get the inventory objects Inventory component
				const auto& destinationInventoryComponent = destinationInventoryObject->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);

				//Remove the dropped gameObject from it's current inventory
				//first get a shared pointer to the object so that the object isnt deallocated
				std::shared_ptr<GameObject> gameObjectSharedPtr = gameObject->parentScene()->getGameObject(gameObject->id()).value();
				sourceInventoryObject->removeItem(gameObjectSharedPtr.get());

				//Add the dropped gameObject to it's new inventory
				destinationInventoryComponent->addItem(gameObjectSharedPtr, slot.value());

				//Refresh the gridDisplayComponent so that it shows the new item
				destinationInventoryComponent->refreshInventoryDisplay();
				sourceInventoryObject->refreshInventoryDisplay();

			}
			//Is this the inventory holding object itself instread of its grid display
			else if (touchingInventoryObject->hasComponent(ComponentTypes::INVENTORY_COMPONENT)) {

				////Get the inventory objects Inventory component
				//const auto& inventoryComponent = inventoryObject->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);

				////Find this GameObjects shared ptr
				//const auto& gameObjectSharedPtr = gameObject->parentScene()->getGameObject(gameObject->id());
				//inventoryComponent->addItem(gameObjectSharedPtr.value());

			}


		}

	}


}
