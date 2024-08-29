#include "ItemDropAction.h"
#include "../components/BBInterfaceComponent.h"

extern std::unique_ptr<Game> game;

void ItemDropAction::perform(GameObject* droppedGameObject)
{

	const auto& objectToInterfaceWith = BBInterfaceComponent::determineItemContactInterfaceTarget(droppedGameObject);

	if (objectToInterfaceWith.has_value()) {

		//Is this being dropped on a object with both inventory and puzzle
		//puzzle has to be solved first before handling inventory, like a locked chest
		if (objectToInterfaceWith.value()->hasTrait(TraitTag::inventory) && objectToInterfaceWith.value()->hasTrait(TraitTag::puzzle)) {

			const auto& puzzleComponent = objectToInterfaceWith.value()->getComponent<PuzzleComponent>(ComponentTypes::PUZZLE_COMPONENT);

			if (puzzleComponent->hasBeenSolved() == false) {
				_handleDropOnPuzzle(objectToInterfaceWith.value().get(), droppedGameObject);
			}
			else {
				_handleDropOnInventory(droppedGameObject, objectToInterfaceWith.value().get());
			}

		}

		//Is it dropped on inventory object
		else if (objectToInterfaceWith.value()->hasTrait(TraitTag::inventory)) {

			if (objectToInterfaceWith.value()->hasState(GameObjectState::LOCKED) == false) {

				_handleDropOnInventory(droppedGameObject, objectToInterfaceWith.value().get());
			}

		}


		//Did we drop onto an puzzle object
		else if (objectToInterfaceWith.value()->hasTrait(TraitTag::puzzle)) {

			const auto& puzzleComponent = objectToInterfaceWith.value()->getComponent<PuzzleComponent>(ComponentTypes::PUZZLE_COMPONENT);
			if (puzzleComponent->hasBeenSolved() == false) {

				_handleDropOnPuzzle(objectToInterfaceWith.value().get(), droppedGameObject);

			}

		}
	}

}


void ItemDropAction::_handleDropOnInventory(GameObject* droppedGameObject, GameObject* destinationInventoryObject)
{

	//The droppedGameObject's parent has to be there because its the inventory that we're moving from
	if (droppedGameObject->parent().has_value()) {

		const auto& droppedObjectInventoryObject = droppedGameObject->parent();
		const auto& sourceInventoryObject = droppedObjectInventoryObject.value()->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);

		//Is this is a shelf type of inventory
		if (destinationInventoryObject->hasTrait(TraitTag::inventory_open) ||
			destinationInventoryObject->hasTrait(TraitTag::inventory_display)) {

			//Get its grid display component
			const auto& gridDisplayComponent = destinationInventoryObject->getComponent<GridDisplayComponent>(ComponentTypes::GRID_DISPLAY_COMPONENT);

			//Get the grid slot that we dropped this object on. if it wasnt close enough to any then we
			//wont move the object
			auto destinationSlot = gridDisplayComponent->getClosestSlot(droppedGameObject->getCenterPosition());
			if (destinationSlot.has_value()) {

				//Get the inventory objects Inventory component
				std::shared_ptr<InventoryComponent> destinationInventoryComponent{};

				if (destinationInventoryObject->hasTrait(TraitTag::inventory_open)) {

					destinationInventoryComponent = destinationInventoryObject->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);
				}
				else if (destinationInventoryObject->hasTrait(TraitTag::inventory_display)) {

					//Get the gameObject that uses this grid display for its inventory
					const auto& destinationInventoryParentObject = destinationInventoryObject->parent().value();

					//Get the inventory objects Inventory component
					destinationInventoryComponent = destinationInventoryParentObject->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);
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

				if (destinationInventoryObject->hasTrait(TraitTag::inventory_open)) {

					destinationInventoryComponent = destinationInventoryObject->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);
				}
				else if (destinationInventoryObject->hasTrait(TraitTag::inventory_display)) {

					//Get the gameObject that uses this grid display for its inventory
					const auto& destinationInventoryParentObject = destinationInventoryObject->parent().value();

					//Get the inventory objects Inventory component
					destinationInventoryComponent = destinationInventoryParentObject->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);
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
					interfaceComponent->setCurrentGameObjectInterfaceActive(destinationInventoryObject);
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
			const auto& destinationInventoryComponent = destinationInventoryObject->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);

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
				interfaceComponent->setCurrentGameObjectInterfaceActive(destinationInventoryObject);
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

	const auto& puzzleComponent = puzzleGameObject->getComponent<PuzzleComponent>(ComponentTypes::PUZZLE_COMPONENT);

	//does this dropped item apply to the puzzle it was dropped on?
	if (puzzleComponent->puzzle->isPuzzlePieceApplicable(droppedGameObject)) {

		//applyPuzzlePiece is a custom method of the puzzle in question and can do its own sound or image animation or whatever
		puzzleComponent->puzzle->applyPuzzlePiece(puzzleGameObject, droppedGameObject);

	}

}
