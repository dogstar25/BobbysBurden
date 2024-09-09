#include "HideAction.h"
#include "../GameConstants.h"
#include "ToggleBobbyEquipAction.h"

void HideAction::perform()
{

	const auto& player = m_parent->parentScene()->getFirstGameObjectByTrait(TraitTag::player);

	if (player.value()->hasState(GameObjectState::HIDING)) {

		_unhideBobby(player.value().get());
		player.value()->removeState(GameObjectState::HIDING);

	}
	else {

		_hideBobby(player.value().get());
		player.value()->addState(GameObjectState::HIDING);


	}

	const auto& animationComponent = m_parent->parent().value()->getComponent<AnimationComponent>(ComponentTypes::ANIMATION_COMPONENT);

	if (player.value()->hasState(GameObjectState::HIDING)) {
		animationComponent->animate("BOBBY_HIDING");
	}
	else{
		animationComponent->animate("IDLE");
	}

}

void HideAction::_hideBobby(GameObject* player)
{
	player->getComponent<PlayerControlComponent>(ComponentTypes::PLAYER_CONTROL_COMPONENT)->disable();
	//player->getComponent<StateComponent>(ComponentTypes::STATE_COMPONENT)->disable();
	//player->disablePhysics();
	player->disableRender();
	player->disableUpdate();

	if (player->hasState(GameObjectState::EQUIPPED)) {
		ToggleBobbyEquipAction action(Json::Value{}, player);
		action.perform();
	}

}

void HideAction::_unhideBobby(GameObject* player)
{
	player->getComponent<PlayerControlComponent>(ComponentTypes::PLAYER_CONTROL_COMPONENT)->enable();
	player->getComponent<StateComponent>(ComponentTypes::STATE_COMPONENT)->enable();
	player->enableUpdate();
	player->enableRender();
}

