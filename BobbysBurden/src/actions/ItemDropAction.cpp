#include "ItemDropAction.h"

extern std::unique_ptr<Game> game;

void ItemDropAction::perform(GameObject* droppedGameObject)
{

	//Did we drop onto an inventory holding gameObject
	if (droppedGameObject->isTouchingByTrait(TraitTag::inventory)) {

		_handleDropOnInventory(droppedGameObject);

	}
	else if (droppedGameObject->isTouchingByTrait(TraitTag::puzzle)) {

		const auto& puzzleObject = droppedGameObject->getFirstTouchingByTrait(TraitTag::puzzle);

		const auto& puzzleComponent = puzzleObject->lock()->getComponent<PuzzleComponent>(ComponentTypes::PUZZLE_COMPONENT);
		if (puzzleComponent->hasBeenSolved() == false) {

			_handleDropOnPuzzle(puzzleObject.value().lock().get(), droppedGameObject);

		}

	}


}

void ItemDropAction::_handleDropOnInventory(GameObject* droppedGameObject)
{

	const auto& touchingInventoryObject = droppedGameObject->getFirstTouchingByTrait(TraitTag::inventory).value().lock();

	if (droppedGameObject->parent().has_value()) {

		const auto& droppedObject = droppedGameObject->parent();
		const auto& sourceInventoryObject = droppedObject.value()->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);

		//Is this is a shelf type of inventory
		if (touchingInventoryObject->hasTrait(TraitTag::inventory_open) ||
			touchingInventoryObject->hasTrait(TraitTag::inventory_display)) {

			//Get its grid display component
			const auto& gridDisplayComponent = touchingInventoryObject->getComponent<GridDisplayComponent>(ComponentTypes::GRID_DISPLAY_COMPONENT);

			//Get the grid slot that we dropped this object on. if it wasnt close enough to any then we
			//wont move the object
			auto destinationSlot = gridDisplayComponent->getClosestSlot(droppedGameObject->getCenterPosition());
			if (destinationSlot.has_value()) {

				//Get the inventory objects Inventory component
				std::shared_ptr<InventoryComponent> destinationInventoryComponent{};

				if (touchingInventoryObject->hasTrait(TraitTag::inventory_open)) {

					destinationInventoryComponent = touchingInventoryObject->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);
				}
				else if (touchingInventoryObject->hasTrait(TraitTag::inventory_display)) {

					//Get the gameObject that uses this grid display for its inventory
					const auto& destinationInventoryObject = touchingInventoryObject->parent().value();

					//Get the inventory objects Inventory component
					destinationInventoryComponent = destinationInventoryObject->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);
				}

				//Remove the dropped gameObject from it's current inventory
				//first get a shared pointer to the object so that the object isnt deallocated
				//std::shared_ptr<GameObject> gameObjectSharedPtr = gameObject->parentScene()->getGameObject(gameObject->id()).value();
				auto currentSourceSlot = sourceInventoryObject->getSlot(droppedGameObject);
				std::shared_ptr<GameObject> gameObjectSharedPtr = sourceInventoryObject->removeItem(droppedGameObject);

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
			//Just add it somewhere if theres an available slot. This shelf or cabinet inventory item
			//probably doesnt show where the slots are so just add it somewhere
			else {

				//Get the inventory objects Inventory component
				std::shared_ptr<InventoryComponent> destinationInventoryComponent{};

				if (touchingInventoryObject->hasTrait(TraitTag::inventory_open)) {

					destinationInventoryComponent = touchingInventoryObject->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);
				}
				else if (touchingInventoryObject->hasTrait(TraitTag::inventory_display)) {

					//Get the gameObject that uses this grid display for its inventory
					const auto& destinationInventoryObject = touchingInventoryObject->parent().value();

					//Get the inventory objects Inventory component
					destinationInventoryComponent = destinationInventoryObject->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);
				}

				//Remove the dropped gameObject from it's current inventory
				//first get a shared pointer to the object so that the object isnt deallocated
				std::shared_ptr<GameObject> gameObjectSharedPtr = droppedGameObject->parentScene()->getGameObject(droppedGameObject->id()).value();
				sourceInventoryObject->removeItem(gameObjectSharedPtr.get());

				//Add the dropped gameObject to it's new inventory
				if (destinationInventoryComponent->addItem(gameObjectSharedPtr) == true) {

					//Refresh the gridDisplayComponent so that it shows the new item
					destinationInventoryComponent->refreshInventoryDisplay();
					sourceInventoryObject->refreshInventoryDisplay();

					//Set the active interface to the inventory we dropped the item to
					//If we don't then the interface of the now offscreen object could never be overridden
					const auto& interfaceComponent = droppedGameObject->getComponent<InterfaceComponent>(ComponentTypes::INTERFACE_COMPONENT);
					interfaceComponent->setCurrentGameObjectInterfaceActive(touchingInventoryObject.get());
				}
				else {
					sourceInventoryObject->addItem(gameObjectSharedPtr);
					std::cout << "Inventory is full!" << std::endl;
				}
			}

		}
		//Is this is drawer or other container that has an inventory - NOT the inventory display grid
		else {

			////Get the inventory objects Inventory component
			const auto& destinationInventoryComponent = touchingInventoryObject->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);

			//Remove the dropped gameObject from it's current inventory
			//first get a shared pointer to the object so that the object isnt deallocated
			std::shared_ptr<GameObject> gameObjectSharedPtr = droppedGameObject->parentScene()->getGameObject(droppedGameObject->id()).value();
			sourceInventoryObject->removeItem(gameObjectSharedPtr.get());

			//Add the dropped gameObject to it's new inventory
			if (destinationInventoryComponent->addItem(gameObjectSharedPtr) == true) {

				//Refresh the gridDisplayComponent so that it shows the new item
				destinationInventoryComponent->refreshInventoryDisplay();
				sourceInventoryObject->refreshInventoryDisplay();

				//Set the active interface to the inventory we dropped the item to
				//If we don't then the interface of the now offscreen object could never be overridden
				const auto& interfaceComponent = droppedGameObject->getComponent<InterfaceComponent>(ComponentTypes::INTERFACE_COMPONENT);
				interfaceComponent->setCurrentGameObjectInterfaceActive(touchingInventoryObject.get());
			}
			else {
				sourceInventoryObject->addItem(gameObjectSharedPtr);
				std::cout << "Inventory is full!" << std::endl;
			}

		}

	}
}

void ItemDropAction::_handleDropOnPuzzle(GameObject* puzzleGameObject, GameObject* droppedGameObject)
{

	//get the puzzle object
	const auto& puzzleObject = droppedGameObject->getFirstTouchingByTrait(TraitTag::puzzle).value().lock();
	const auto& puzzleComponent = puzzleObject->getComponent<PuzzleComponent>(ComponentTypes::PUZZLE_COMPONENT);

	//does this dropped item apply to the puzzle it was dropped on?
	if (puzzleComponent->puzzle->isPuzzlePieceApplicable(droppedGameObject)) {

		//applyPuzzlePiece is a custom method of the puzzle in question and can do its own sound or image animation or whatever
		puzzleComponent->puzzle->applyPuzzlePiece(puzzleGameObject, droppedGameObject);

	}

}
