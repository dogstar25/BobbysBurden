#include "SkullPuzzle.h"



SkullPuzzle::SkullPuzzle(std::string name, std::string clue, int pieceCount)
	:Puzzle(name, clue, pieceCount)
{


}

bool SkullPuzzle::isPuzzlePieceApplicable(GameObject* puzzlePieceObject)
{

	bool isApplicable = false;

	//Piece 1
	if (puzzlePieceObject->type() == "DIAMOND") {

		isApplicable = true;
	}
	if (puzzlePieceObject->type() == "EMERALD") {

		isApplicable = true;
	}

	return isApplicable;

}

void SkullPuzzle::applyPuzzlePiece(GameObject* puzzleObject, GameObject* puzzlePieceObject)
{

	if (hasBeenSolved() == false) {

		//Piece 1
		if (puzzlePieceObject->type() == "DIAMOND") {

			m_pieces[0] = true;

		}

		//Piece 2
		if (puzzlePieceObject->type() == "EMERALD") {

			m_pieces[1] = true;

		}

		//Create an unlock image to indicated the puzzle piece application worked
		auto position = puzzleObject->getCenterPosition();
		auto mapPosition = util::pixelToTileLocation(position.x, position.y);

		const auto& unlockObject = puzzlePieceObject->parentScene()->
			addGameObject("UNLOCK_ICON", nullptr, GameLayer::FOREGROUND_4, (float)mapPosition.x - 1, (float)mapPosition.y, (float)0);

		unlockObject->setSize({ 32.0, 32.0 });

		puzzlePieceObject->setRemoveFromWorld(true);

		//un-hide emeral or the diamond
		const auto& childrenComponent = puzzleObject->getComponent<ChildrenComponent>(ComponentTypes::CHILDREN_COMPONENT);
		childrenComponent->getFirstChildByType(puzzlePieceObject->type()).value()->enableRender();

		//change animation state of skull
		if (hasBeenSolved()) {
			//puzzleObject->addState(GameObjectState::SOLVED);

			//un-hide the key
			const auto& childrenComponent = puzzleObject->getComponent<ChildrenComponent>(ComponentTypes::CHILDREN_COMPONENT);
			const auto& keyObject = childrenComponent->getFirstChildByType("SMALL_KEY").value();
			keyObject->enableRender();
			keyObject->addState(GameObjectState::ITEM_OBTAINABLE);
			keyObject->addState(GameObjectState::ITEM_LOOSE);
			//keyObject->enableUpdate();


			//disable the puzzle so that it is no long active
			puzzleObject->disableUpdate();

			const auto& animationComponent = puzzleObject->getComponent<AnimationComponent>(ComponentTypes::ANIMATION_COMPONENT);
			animationComponent->animate("SOLVED");

			//For a subtle affect, we have a light object on the jewesl in the skull, so we have to turn them on
			StateComponent::propogateStateToAllChildren(puzzleObject, GameObjectState::ON);

		}

		

	}
 }
