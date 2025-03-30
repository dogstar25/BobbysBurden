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
	return BrainState::PATROL;
}

void BBGhostBrainComponent::_doPatrol()
{

	NavigationStatus navigationCode{};
	auto navigationComponent = parent()->getComponent<NavigationComponent>(ComponentTypes::NAVIGATION_COMPONENT);

	if (m_focusPoint.has_value() == false) {
		m_focusPoint = _getNextPatrolDestination();
	}

	//navigationCode = navigationComponent->navigateTo(m_focusPoint.value().x, m_focusPoint.value().y);
	if (navigationCode == NavigationStatus::DESTINATION_REACHED) {
		m_focusPoint = _getNextPatrolDestination();
		assert(m_focusPoint.has_value() && "No Patrol Destination was set");
	}
	else if (navigationCode == NavigationStatus::NO_PATH_FOUND) {
		m_focusPoint = _getNextPatrolDestination();
		//std::cout << "Drone! No path was found for navigation!" << std::endl;
	}
	else if (navigationCode == NavigationStatus::STUCK) {

		if (m_currentState == BrainState::PATROL) {
			m_focusPoint = _getNextPatrolDestination();
		}
	}


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

SDL_FPoint BBGhostBrainComponent::_getNextPatrolDestination()
{

	SDL_FPoint newPatrolLocation{};

	//Get the next waypoint in the list
	//If we have reached the end then randomly resort the waypoints and reset to zero
	if (m_currentWaypointIndex == m_wayPoints.size() - 1) {

		m_currentWaypointIndex = 0;
		unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
		std::shuffle(m_wayPoints.begin(), m_wayPoints.end(), std::default_random_engine(seed));

	}
	else {
		m_currentWaypointIndex += 1;
	}

	auto newDestination = m_wayPoints[m_currentWaypointIndex];
	newPatrolLocation = newDestination.lock().get()->getCenterPosition();

	return newPatrolLocation;


}