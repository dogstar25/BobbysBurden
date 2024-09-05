#include "MermaidMantlePuzzle.h"


MermaidMantlePuzzle::MermaidMantlePuzzle(std::string name, std::string clue, int pieceCount, GameObject* parent)
	:Puzzle(name, clue, pieceCount, parent)
{


}

bool MermaidMantlePuzzle::isPuzzlePieceApplicable(GameObject* puzzlePieceObject)
{

	bool isApplicable = false;

	//Piece 1
	if (puzzlePieceObject->type() == "MERMAID_1") {

		isApplicable = true;
	}

	return isApplicable;

}

void MermaidMantlePuzzle::applyPuzzlePiece(GameObject* puzzleObject, GameObject* puzzlePieceObject)
{

	if (hasBeenSolved() == false) {

		//Piece 1
		if (puzzlePieceObject->type() == "MERMAID_1") {

			m_pieces[0] = true;

		}

		//Create an unlock image to indicated the puzzle piece application worked
		auto position = puzzleObject->getCenterPosition();
		auto mapPosition = util::pixelToTileLocation(position.x, position.y);

		const auto& unlockObject = puzzlePieceObject->parentScene()->
			addGameObject("UNLOCK_ICON", nullptr, GameLayer::FOREGROUND_4, (float)mapPosition.x - 1, (float)mapPosition.y, (float)0);

		unlockObject->setSize({ 32.0, 32.0 });

		puzzlePieceObject->setRemoveFromWorld(true);

		//un-hide the mermaid statue on the mantle
		const auto& childrenComponent = puzzleObject->parent().value()->getComponent<ChildrenComponent>(ComponentTypes::CHILDREN_COMPONENT);
		childrenComponent->getFirstChildByType("MERMAID_1").value()->enableRender();

		//Execute the bookshelf move action automatically
		const auto& bookcase = puzzleObject->parentScene()->getFirstGameObjectByName("denBookcase");
		if (bookcase.has_value()) {
			const auto& bookcaseActionComponent = bookcase.value()->getComponent<ActionComponent>(ComponentTypes::ACTION_COMPONENT);
			const auto& moveAction = bookcaseActionComponent->getAction(Actions::MOVE);
			moveAction->perform(bookcase.value().get());
		}

		//Unhide The secret doorknob
		const auto& doorKnob = puzzleObject->parentScene()->getFirstGameObjectByName("secretDenDoorknob");
		doorKnob.value()->enableRender();

		//Activate Update for the secret door
		const auto& secretDenDoor = puzzleObject->parentScene()->getFirstGameObjectByName("secretDenDoor");
		secretDenDoor.value()->enableUpdate();

		//light the canle on the shelf
		const auto& candle = puzzleObject->parentScene()->getFirstGameObjectByName("denCandleSecretDoor");
		//candle.value()->addState(GameObjectState::ON);
		std::shared_ptr<Action> onOffToggleAction = std::make_shared<OnOffToggleAction>(Json::Value(), candle.value().get());
		onOffToggleAction->perform(candle.value().get());

		//disable the puzzle so that it is no long active
		puzzleObject->disableUpdate();

	}
 }
