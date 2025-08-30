#include "TwistBedKnobAction.h"
#include "../GameConstants.h"

void TwistBedKnobAction::perform()
{
	std::cout << "Twisted the bedknob!" << std::endl;

	//Get bedObject
	auto bedPosition = m_parent->parent().value()->getCenterPosition();

	bedPosition.x += 64;
	bedPosition.y -= 20;

	auto newPosition = bedPosition;
	auto tilePosition = util::pixelToTileLocation(newPosition.x, newPosition.y);
	tilePosition.x -= 2;
	tilePosition.y += 3;

	const auto& keyObject = m_parent->parentScene()->addGameObject("KEY1", nullptr, GameLayer::BACKGROUND_3, 
		static_cast<float>(tilePosition.x), static_cast<float>(tilePosition.y));
	keyObject->addLitHighlight( {128.0,128.0} );
	keyObject->addState(GameObjectState::ITEM_LOOSE);
	keyObject->addState(GameObjectState::ITEM_OBTAINABLE);

	//disable this puzzle object so that the action can only be triggered once
	m_parent->disableUpdate();
	

}

