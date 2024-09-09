#include "PushGuestBedButtonAction.h"
#include "../GameConstants.h"

void PushGuestBedButtonAction::perform()
{

	//Get bedObject
	auto bedPosition = m_parent->parent().value()->getCenterPosition();

	bedPosition.x += 0;
	bedPosition.y += 0;

	auto newPosition = bedPosition;
	auto tilePosition = util::pixelToTileLocation(newPosition.x, newPosition.y);
	tilePosition.x -= 0;
	tilePosition.y += 2;

	const auto& keyObject = m_parent->parentScene()->addGameObject("BED_STAIRS_BLOCK", nullptr, GameLayer::BACKGROUND_3, tilePosition.x, tilePosition.y);

	//disable this puzzle object so that the action can only be triggered once
	m_parent->setRemoveFromWorld(true);
	

}

