#include "BBGhostBrainComponent.h"
#include <algorithm>
#include <random>

BBGhostBrainComponent::BBGhostBrainComponent(Json::Value definitionJSON, GameObject* parent)
	: BrainComponent(definitionJSON, parent)
{

	m_manualWayPoints = {

		{ 20, 139 },
		{56,139},
		{56,150},
		{20,150}

	};

}

void BBGhostBrainComponent::postInit()
{
	BrainComponent::postInit();

	for (const auto waypoint : m_manualWayPoints) {

		const auto navObject = parent()->parentScene()->createGameObject("NAVIGATION_WAYPOINT", nullptr,
			waypoint.x, waypoint.y, 0.0f, parent()->parentScene(), GameLayer::ABSTRACT);

		m_wayPoints.push_back(navObject);

	}

	unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
	std::shuffle(m_wayPoints.begin(), m_wayPoints.end(), std::default_random_engine(seed));

	auto vitalityComponent = parent()->getComponent<VitalityComponent>(ComponentTypes::VITALITY_COMPONENT);
	m_normalSpeed = vitalityComponent->speed();
	m_huntSpeed = m_normalSpeed * 3.0f;
}

int BBGhostBrainComponent::_determineState()
{

	_updateLastSeenBobbyPosition();

	bool bobbyVisible = !seenObjects().empty();

	switch (m_currentState) {

	case BrainState::PATROL:
		if (bobbyVisible) {
			m_alertTimer.reset();
			return BrainState::ALERT;
		}
		return BrainState::PATROL;

	case BrainState::ALERT:
		if (m_alertTimer.hasMetTargetDuration()) {
			parent()->getComponent<VitalityComponent>(ComponentTypes::VITALITY_COMPONENT)->setSpeed(m_huntSpeed);
			return BrainState::ENGAGE;
		}
		return BrainState::ALERT;

	case BrainState::ENGAGE:
		return BrainState::ENGAGE;

	default:
		return BrainState::PATROL;
	}

}

void BBGhostBrainComponent::_updateLastSeenBobbyPosition()
{
	if (!seenObjects().empty()) {
		auto& seenObject = seenObjects().front();
		if (!seenObject.gameObject.expired()) {
			m_lastSeenBobbyPosition = seenObject.gameObject.lock()->getCenterPosition();
		}
	}
}

void BBGhostBrainComponent::_doIdle()
{
}

void BBGhostBrainComponent::_doPatrol()
{

	NavigationStatus navigationCode{};
	auto navigationComponent = parent()->getComponent<NavigationComponent>(ComponentTypes::NAVIGATION_COMPONENT);

	if (m_focusPoint.has_value() == false) {
		m_focusPoint = _getNextPatrolDestination();
	}

	navigationCode = navigationComponent->navigateTo(m_focusPoint.value().x, m_focusPoint.value().y);
	if (navigationCode == NavigationStatus::DESTINATION_REACHED) {
		m_focusPoint = _getNextPatrolDestination();
		assert(m_focusPoint.has_value() && "No Patrol Destination was set");
	}
	else if (navigationCode == NavigationStatus::NO_PATH_FOUND) {
		m_focusPoint = _getNextPatrolDestination();
	}
	else if (navigationCode == NavigationStatus::STUCK) {

		if (m_currentState == BrainState::PATROL) {
			m_focusPoint = _getNextPatrolDestination();
		}
	}

}

void BBGhostBrainComponent::_doAlert()
{
	// Ghost has spotted Bobby - hold position for alertTimer duration
	// No navigation call here keeps the ghost frozen in place
}

void BBGhostBrainComponent::_doEngage()
{

	auto navigationComponent = parent()->getComponent<NavigationComponent>(ComponentTypes::NAVIGATION_COMPONENT);

	NavigationStatus navigationCode = navigationComponent->navigateTo(
		m_lastSeenBobbyPosition.x, m_lastSeenBobbyPosition.y);

	// If Bobby's last known spot is reached without finding him, keep circling there.
	// The ghost is relentless once it has detected its target.
	if (navigationCode == NavigationStatus::NO_PATH_FOUND ||
		navigationCode == NavigationStatus::STUCK) {
		m_focusPoint = _getNextPatrolDestination();
		navigationComponent->navigateTo(m_focusPoint.value().x, m_focusPoint.value().y);
	}

}

void BBGhostBrainComponent::update()
{
	BrainComponent::update();

	m_currentState = _determineState();

	switch (m_currentState) {

	case BrainState::PATROL:
		_doPatrol();
		break;
	case BrainState::ALERT:
		_doAlert();
		break;
	case BrainState::ENGAGE:
		_doEngage();
		break;
	default:
		_doIdle();
		break;
	}

}

SDL_FPoint BBGhostBrainComponent::_getNextPatrolDestination()
{

	SDL_FPoint newPatrolLocation{};

	if (m_currentWaypointIndex == m_wayPoints.size() - 1) {

		m_currentWaypointIndex = 0;
		unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
		std::shuffle(m_wayPoints.begin(), m_wayPoints.end(), std::default_random_engine(seed));

	}
	else {
		m_currentWaypointIndex += 1;
	}

	auto newDestination = m_wayPoints[m_currentWaypointIndex];
	newPatrolLocation = newDestination.get()->getCenterPosition();

	return newPatrolLocation;

}
