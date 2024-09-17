#include "PlayPhonographAction.h"
#include "../GameConstants.h"

void PlayPhonographAction::perform()
{

	const auto& childrenComponent = m_parent->getComponent<ChildrenComponent>(ComponentTypes::CHILDREN_COMPONENT);
	const auto& inventoryObject = childrenComponent->getFirstChildByTrait(TraitTag::inventory);

	const auto& inventoryComponent = inventoryObject.value()->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);
	const auto& record = inventoryComponent->getFirstByType("RECORD");

	if (record.has_value()) {

		if (m_parent->hasState(GameObjectState::ON)) {

			m_parent->addState(GameObjectState::OFF);
			record.value()->addState(GameObjectState::ITEM_OBTAINABLE);
			record.value()->addState(GameObjectState::DRAGGABLE);
			_handleRecord(record.value());

		}
		else {

			m_parent->addState(GameObjectState::ON);
			record.value()->removeState(GameObjectState::ITEM_OBTAINABLE);
			record.value()->removeState(GameObjectState::DRAGGABLE);
			_handleRecord(record.value());

		}

	}
	else {

		//play a screech sound

	}


}

void PlayPhonographAction::_handleRecord(std::shared_ptr<GameObject> record)
{

	const auto& soundComponent = m_parent->getComponent<SoundComponent>(ComponentTypes::SOUND_COMPONENT);


	if (record->name() == "cellarSong") {

		if (m_parent->hasState(GameObjectState::OFF)) {
			soundComponent->stopSound("CELLAR_SONG");
		}
		else if (m_parent->hasState(GameObjectState::ON)) {
			soundComponent->playSound("CELLAR_SONG");
		}

	}




}

