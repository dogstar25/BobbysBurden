#include "BBGhostBrainComponent.h"


BBGhostBrainComponent::BBGhostBrainComponent(Json::Value definitionJSON, GameObject* parent)
	: BrainComponent(definitionJSON, parent)
{



}

void BBGhostBrainComponent::postInit()
{
	//Call base brain postinit
	BrainComponent::postInit();


	//Store a 





	//Get all WayPoints
	//for (const auto& gameObject : parent()->parentScene()->getGameObjectsByTrait(TraitTag::waypoint)) {

	//	m_wayPoints.push_back(gameObject);
	//}

	////Do an random sort of the waypoints order
	//unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
	//std::shuffle(m_wayPoints.begin(), m_wayPoints.end(), std::default_random_engine(seed));

}

int BBGhostBrainComponent::_determineState()
{
	return 0;
}

void BBGhostBrainComponent::_doPatrol()
{
}

void BBGhostBrainComponent::_doEngage()
{
}

void BBGhostBrainComponent::update()
{
	//Call base update
	BrainComponent::update();

	//Determine state
	m_currentState = _determineState();

	switch (m_currentState) {

	case BrainState::PATROL:
		_doPatrol();
		break;
	case BrainState::ENGAGE:
		_doEngage();
		break;
	default:
		_doPatrol();
		break;
	}

}