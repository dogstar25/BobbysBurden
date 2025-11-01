#include "BBMaskedOverlayComponent.h"
#include "../GameConstants.h"


//extern std::unique_ptr<Game> game;

BBMaskedOverlayComponent::BBMaskedOverlayComponent(Json::Value componentJSON, GameObject* parent, Scene* parentScene) :
	MaskedOverlayComponent(componentJSON, parent, parentScene)
{

}

void BBMaskedOverlayComponent::update()
{

	//loop through all masks and turn on ones that are associated with rooms
	//that Bobby can see and turn off ones associated with rooms he cannot
	const auto& player = parent()->parentScene()->player();
	for(const auto& mask : m_maskObjects){

		auto hasLineOfSight = util::hasLineOfSight(player.get(), mask.get(), parent()->parentScene()->physicsWorld());
		if (hasLineOfSight.has_value()) {

			mask->addState(GameObjectState::ON);

		}
		else {
			mask->addState(GameObjectState::OFF);
		}

	}

	MaskedOverlayComponent::update();

}


