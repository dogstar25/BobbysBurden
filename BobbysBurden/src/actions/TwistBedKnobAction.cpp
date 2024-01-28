#include "TwistBedKnobAction.h"
#include "../GameConstants.h"

void TwistBedKnobAction::perform(GameObject* gameObject)
{
	std::cout << "Twisted the bedknob!" << std::endl;

	//Get bedObject
	auto bedPosition = gameObject->parent().value()->getCenterPosition();

	bedPosition.x += 64;
	bedPosition.y += 12;

	auto newPosition = bedPosition;
	auto tilePosition = util::pixelToTileLocation(newPosition.x, newPosition.y);
	tilePosition.x -= 2;
	tilePosition.y += 3;

	const auto& keyObject = gameObject->parentScene()->addGameObject("KEY1", GameLayer::BACKGROUND_3, tilePosition.x, tilePosition.y);
	keyObject->addLitHighlight( {128.0,128.0} );
	keyObject->addState(GameObjectState::ITEM_LOOSE);
	keyObject->addState(GameObjectState::ITEM_OBTAINABLE);

	//disable this puzzle object so that the action can only be triggered once
	gameObject->disableUpdate();
	

}

