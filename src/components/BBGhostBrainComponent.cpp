#include "BBGhostBrainComponent.h"

#include "BBStateComponent.h"
#include "GameConstants.h"

#include <algorithm>
#include <random>   

BBGhostBrainComponent::BBGhostBrainComponent(Json::Value definitionJSON, GameObject* parent)
	: BrainComponent(definitionJSON, parent)
{
	m_wayPoints.resize(static_cast<size_t>(houseZone::COUNT));


	SDL_FPoint bathroomDoorLocation = { 17.f, 139.f };

	m_wayPoints[static_cast<int>(houseZone::mainHouse)] = {
		{ 20, 139 }, { 56,139 }, { 56,150 }, { 20,150 }, { 20,128 }, bathroomDoorLocation
	};

	m_wayPoints[static_cast<int>(houseZone::bathroom)] = {
		{ 29, 72 }, { 45,72 }
	};

}

void BBGhostBrainComponent::postInit()
{
	//Call base brain postinit
	BrainComponent::postInit();

	//Do an random sort of the waypoints order
	unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
	std::shuffle(m_wayPoints[(int)houseZone::mainHouse].begin(), m_wayPoints[(int)houseZone::mainHouse].end(), std::default_random_engine(seed));

}

int BBGhostBrainComponent::_determineState()
{

	//Do we see Bobby? If so, engage
	for (const auto& seenObject : m_seenObjects) {

		if (seenObject.gameObject.expired() == false) {
			if (seenObject.gameObject.lock()->hasTrait(TraitTag::player)) {

				//If Bobby is hiding, then we cant see him
				const auto& stateComponent = seenObject.gameObject.lock()->getComponent<BBStateComponent>(ComponentTypes::STATE_COMPONENT);
				if (stateComponent->testState(GameObjectState::HIDING)) {
					break;
				}
				else {
					return BrainState::ENGAGE;
				}
			}
		}

	}

	return BrainState::PATROL;
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


	//Handle if the ghost is traveling from the attic door to the attic, hide him so it looks like he
	//must be using the unseen starirs
	auto stateComponent = parent()->getComponent<BBStateComponent>(ComponentTypes::STATE_COMPONENT);
	auto tilePosition = parent()->getTilePosition();
	if ((tilePosition.y < 138 && tilePosition.y > 128)) {
		stateComponent->addState(GameObjectState::DISABLED_RENDER);
	}
	else {
		stateComponent->removeState(GameObjectState::DISABLED_RENDER);
	}

	//Execute the pathfinding and navigation movement
	navigationCode = navigationComponent->navigateTo(m_focusPoint.value().x, m_focusPoint.value().y);

	//Ghost has reached the destination
	if (navigationCode == NavigationStatus::DESTINATION_REACHED) {

		//If we are currently touching a Door Entry Point, for a front door or a side door,  then we will use the door warping logic to 
		//take the ghost to the detached room, then reset his focus point so that its gets reset on the next pass
		//we cant set the focus point immediately because the warp to the room hasnt refreshed with the physics(box2d)
		if (parent()->isTouchingByType("DOOR_FRONT_ENTRY_POINT") || parent()->isTouchingByType("DOOR_SIDE_ENTRY_POINT")) {

			_handleDetachedRoomNavigation();
			m_focusPoint = std::nullopt;
			return;
		}

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

	//Flash Red
	auto const& animationComponent = parent()->getComponent<AnimationComponent>(ComponentTypes::ANIMATION_COMPONENT);
	animationComponent->setFlash(Colors::RED, .2, 10);



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
		_doIdle();
		break;
	}

}

SDL_FPoint BBGhostBrainComponent::_getNextPatrolDestination()
{

	SDL_FPoint newPatrolLocation{};

	int houseZoneIndex = static_cast<int> (_getCurrentHouseZoneIndex());
	//Get the next waypoint in the list
	//If we have reached the end or we have changed house zones, then randomly resort the waypoints and reset to zero
	if (m_currentWaypointIndex == m_wayPoints[houseZoneIndex].size() - 1 || (houseZoneIndex != m_lastHouseZoneIndex)) {

		m_currentWaypointIndex = 0;
		m_lastHouseZoneIndex = houseZoneIndex;

		//Only randomly shuffle the main house way points to make it random
		if (houseZoneIndex == static_cast<int>(houseZone::mainHouse)) {

			unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
			std::shuffle(m_wayPoints[houseZoneIndex].begin(), m_wayPoints[houseZoneIndex].end(), std::default_random_engine(seed));
		}

	}
	else {
		m_currentWaypointIndex += 1;
	}

	newPatrolLocation = util::tileToPixelLocation(
		m_wayPoints[houseZoneIndex][m_currentWaypointIndex].x,
		m_wayPoints[houseZoneIndex][m_currentWaypointIndex].y);

	return newPatrolLocation;


}

bool BBGhostBrainComponent::_isInMainHouseRoom()
{

	if (parent()->isTouchingByType("BOBBYS_ROOM") ||
		parent()->isTouchingByType("PARLOR_ROOM") ||
		parent()->isTouchingByType("GUEST_BEDROOM") ||
		parent()->isTouchingByType("DEN_ROOM") ||
		parent()->isTouchingByType("FRONT_TOP_STAIRS_ROOM") ||
		parent()->isTouchingByType("ATTIC_ROOM") ||
		parent()->isTouchingByType("FRONT_BOT_STAIRS_ROOM"))
	{
		return true;
	}

	return false;


}

bool BBGhostBrainComponent::_isInBobbysBathroomRoom()
{

	if (parent()->isTouchingByType("BOBBYS_BATHROOM"))
	{
		return true;
	}

	return false;


}

bool BBGhostBrainComponent::_isInAtticRoom()
{

	if (parent()->isTouchingByType("ATTIC_ROOM"))
	{
		return true;
	}

	return false;


}

bool BBGhostBrainComponent::_isInHiddenRoom()
{

	return false;


}

bool BBGhostBrainComponent::_isInKitchenRoom()
{

	return false;


}

bool BBGhostBrainComponent::_isDestinationDetachedRoom()
{

	SDL_Point focusPoint = util::pixelToTileLocation(m_focusPoint->x, m_focusPoint->y);;

	//bathroom
	if (focusPoint.x == m_BathroomDestination.x &&
		focusPoint.y == m_BathroomDestination.y) {

		return true;
	}


	return false;
}

void BBGhostBrainComponent::_handleDetachedRoomNavigation()
{

	// Get the door entry point object's action and execute it, which will warp the ghost
// to the matching door (detached room destination).
	std::optional<std::weak_ptr<GameObject>> doorEntryObject;

	if (parent()->isTouchingByType("DOOR_FRONT_ENTRY_POINT")) {
		doorEntryObject = parent()->getFirstTouchingByType("DOOR_FRONT_ENTRY_POINT");
	}
	else if (parent()->isTouchingByType("DOOR_SIDE_ENTRY_POINT")) {
		doorEntryObject = parent()->getFirstTouchingByType("DOOR_SIDE_ENTRY_POINT");
	}

	if (!doorEntryObject.has_value()) {
		SDL_assert(!"No Door Entry Point was found when trying to handle detached room navigation!");
		return;
	}

	auto doorEntry = doorEntryObject->lock();
	if (!doorEntry) {
		return;
	}

	auto action = doorEntry
		->getComponent<ActionComponent>(ComponentTypes::ACTION_COMPONENT)
		->getAction(Actions::GHOST_DOOR_ENTER);

	action->perform();


}

BBGhostBrainComponent::houseZone BBGhostBrainComponent::_getCurrentHouseZoneIndex()
{
	if (_isInMainHouseRoom()) {
		return houseZone::mainHouse;
	}
	else if (_isInBobbysBathroomRoom()) {
		return houseZone::bathroom;
	}
	// Add a default return to avoid warnings/errors
	return houseZone::mainHouse;
}
