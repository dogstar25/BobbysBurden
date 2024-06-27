#include "BBMaskedOverlayComponent.h"
#include "../GameConstants.h"


extern std::unique_ptr<Game> game;

BBMaskedOverlayComponent::BBMaskedOverlayComponent(Json::Value componentJSON, GameObject* parent, Scene* parentScene) :
	MaskedOverlayComponent(componentJSON, parent, parentScene)
{

}

void BBMaskedOverlayComponent::update()
{

	//loop through all masks and turn on ones that are associated with rooms
	//that Bobby can see and turn off ones associated with rooms he cannot
	const auto& player = parent()->parentScene()->getFirstGameObjectByTrait(TraitTag::player).value().get();
	for(const auto& mask : m_maskObjects){

		if (util::hasLineOfSight(player, mask.get())) {

			mask->addState(GameObjectState::ON);

		}
		else {
			mask->addState(GameObjectState::OFF);
		}

	}

	MaskedOverlayComponent::update();

}

bool BBMaskedOverlayComponent::_hasLineOfSight(SDL_FPoint playerPosition, SDL_FPoint maskPosition)
{
	bool clearPath{ true };


	util::toBox2dPoint(playerPosition);
	util::toBox2dPoint(maskPosition);

	//cast a physics raycast from the light object to the center of this lightedArea's center
	parent()->parentScene()->physicsWorld()->RayCast(&RayCastCallBack::instance(),
		{ playerPosition.x, playerPosition.y }, { maskPosition.x, maskPosition.y });

	//Loop through all objects hit between the player and the center of the mask area
	for (BrainRayCastFoundItem rayHitObject : RayCastCallBack::instance().intersectionItems()) {

		//Is this a barrier or and also NOT its own body and the object is not physicsdisabled
		if ((rayHitObject.gameObject->hasTrait(TraitTag::barrier) || rayHitObject.gameObject->hasState(GameObjectState::IMPASSABLE)) &&
			rayHitObject.gameObject != parent()) {
			clearPath = false;
			break;
		}
	}

	RayCastCallBack::instance().reset();

	return clearPath;

}

