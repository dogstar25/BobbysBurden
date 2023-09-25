#include "ItemDropAction.h"

extern std::unique_ptr<Game> game;

void ItemDropAction::perform(GameObject* gameObject)
{

	//If there was a overlay added to the dragging somewhere then make sure its clear
	const auto& renderComponent = gameObject->getComponent<RenderComponent>(ComponentTypes::RENDER_COMPONENT);
	renderComponent->removeDisplayOverlay();

	//Did we drop onto an inventory holding gameObject
	if (gameObject->isTouchingByTrait(TraitTag::inventory)) {


		const auto& touchingInventoryObject = gameObject->getFirstTouchingByTrait(TraitTag::inventory).value().lock();


		if (gameObject->parent().has_value() ) {

			const auto& droppedObject = gameObject->parent();
			const auto& sourceInventoryObject = droppedObject.value()->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);

			//Is this is a shelf type of inventory
			if (touchingInventoryObject->hasComponent(ComponentTypes::INVENTORY_COMPONENT) &&
				touchingInventoryObject->hasComponent(ComponentTypes::GRID_DISPLAY_COMPONENT)) {

				//Get its grid display component
				const auto& gridDisplayComponent = touchingInventoryObject->getComponent<GridDisplayComponent>(ComponentTypes::GRID_DISPLAY_COMPONENT);

				//Get the grid slot that we dropped this object on. if it wasnt close enough to any then we
				//wont move the object
				auto destinationSlot = gridDisplayComponent->getClosestSlot(gameObject->getCenterPosition());
				if (destinationSlot.has_value()) {

					//Get the inventory objects Inventory component
					const auto& destinationInventoryComponent = touchingInventoryObject->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);

					//Remove the dropped gameObject from it's current inventory
					//first get a shared pointer to the object so that the object isnt deallocated
					//std::shared_ptr<GameObject> gameObjectSharedPtr = gameObject->parentScene()->getGameObject(gameObject->id()).value();
					auto currentSourceSlot = sourceInventoryObject->getSlot(gameObject);
					std::shared_ptr<GameObject> gameObjectSharedPtr = sourceInventoryObject->removeItem(gameObject);

					//IF there is already an object in this slot then get a reference to it also so that we can swap places with the object we're dropping
					if (destinationInventoryComponent->hasItem(destinationSlot.value())) {

						std::shared_ptr<GameObject> swapObjectSharedPtr = destinationInventoryComponent->removeItem(destinationSlot.value());
						sourceInventoryObject->addItem(swapObjectSharedPtr, currentSourceSlot.value());

					}

					//Add the dropped gameObject to it's new inventory
					destinationInventoryComponent->addItem(gameObjectSharedPtr, destinationSlot.value());

					//Refresh the gridDisplayComponent so that it shows the new item
					destinationInventoryComponent->refreshInventoryDisplay();
					sourceInventoryObject->refreshInventoryDisplay();

				}

			}
			//Is this is drawer or other container that has an inventory - NOT the inventory display grid
			else if (touchingInventoryObject->hasComponent(ComponentTypes::INVENTORY_COMPONENT) &&
					touchingInventoryObject->hasComponent(ComponentTypes::GRID_DISPLAY_COMPONENT) == false) {

				////Get the inventory objects Inventory component
				const auto& destinationInventoryComponent = touchingInventoryObject->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);

				//Remove the dropped gameObject from it's current inventory
				//first get a shared pointer to the object so that the object isnt deallocated
				std::shared_ptr<GameObject> gameObjectSharedPtr = gameObject->parentScene()->getGameObject(gameObject->id()).value();
				sourceInventoryObject->removeItem(gameObjectSharedPtr.get());

				//Add the dropped gameObject to it's new inventory
				if (destinationInventoryComponent->addItem(gameObjectSharedPtr) == true) {

					//Refresh the gridDisplayComponent so that it shows the new item
					destinationInventoryComponent->refreshInventoryDisplay();
					sourceInventoryObject->refreshInventoryDisplay();

					//Set the active interface to the inventory we dropped the item to
					//If we don't then the interface of the now offscreen object could never be overridden
					const auto& interfaceComponent = gameObject->getComponent<InterfaceComponent>(ComponentTypes::INTERFACE_COMPONENT);
					interfaceComponent->setCurrentGameObjectInterfaceActive(touchingInventoryObject.get());
				}
				else {
					sourceInventoryObject->addItem(gameObjectSharedPtr);
					std::cout << "Inventory is full!" << std::endl;
				}


			}
			//This is the inventory grid display of the inventory holding obbject
			else if (touchingInventoryObject->hasComponent(ComponentTypes::INVENTORY_COMPONENT) == false &&
				touchingInventoryObject->hasComponent(ComponentTypes::GRID_DISPLAY_COMPONENT) == true) {

				//This is a grid display object so get its grid display component
				const auto& gridDisplayComponent = touchingInventoryObject->getComponent<GridDisplayComponent>(ComponentTypes::GRID_DISPLAY_COMPONENT);

				//Get the grid slot that we dropped this object on. if it wasnt close enough to any then we
				//wont move the object
				auto destinationSlot = gridDisplayComponent->getClosestSlot(gameObject->getCenterPosition());
				if (destinationSlot.has_value()) {

					//Get the gameObject that uses this grid display for its inventory
					const auto& destinationInventoryObject = touchingInventoryObject->parent().value();

					//Get the inventory objects Inventory component
					const auto& destinationInventoryComponent = destinationInventoryObject->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);

					//Remove the dropped gameObject from it's current inventory
					//first get a shared pointer to the object so that the object isnt deallocated
					//std::shared_ptr<GameObject> gameObjectSharedPtr = gameObject->parentScene()->getGameObject(gameObject->id()).value();
					auto currentSourceSlot = sourceInventoryObject->getSlot(gameObject);
					std::shared_ptr<GameObject> gameObjectSharedPtr = sourceInventoryObject->removeItem(gameObject);

					//IF there is already an object in this slot then get a reference to it also so that we can swap places with the object we're dropping
					if (destinationInventoryComponent->hasItem(destinationSlot.value())) {

						std::shared_ptr<GameObject> swapObjectSharedPtr = destinationInventoryComponent->removeItem(destinationSlot.value());
						sourceInventoryObject->addItem(swapObjectSharedPtr, currentSourceSlot.value());

					}

					//Add the dropped gameObject to it's new inventory
					destinationInventoryComponent->addItem(gameObjectSharedPtr, destinationSlot.value());

					//Refresh the gridDisplayComponent so that it shows the new item
					destinationInventoryComponent->refreshInventoryDisplay();
					sourceInventoryObject->refreshInventoryDisplay();

				}

			}

		}
	}


}
