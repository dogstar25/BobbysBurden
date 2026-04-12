#pragma once
#include "MobyDick.h"

class BBGhostBrainComponent :  public BrainComponent
{

	enum class houseZone {

		mainHouse = 0,
		bathroom,

		COUNT

	};

public:

	BBGhostBrainComponent(Json::Value definitionJSON, GameObject* parent);

	void update() override;
	void postInit() override;

private:
	std::vector<std::vector<SDL_FPoint>> m_wayPoints{};


	int _determineState();
	void _doPatrol();
	void _doEngage();
	void _doIdle();
	SDL_FPoint _getNextPatrolDestination();
	bool _isInMainHouseRoom();
	bool _isInBobbysBathroomRoom();
	bool _isInAtticRoom();
	bool _isInHiddenRoom();
	bool _isInKitchenRoom();

	bool _isDestinationDetachedRoom();
	void _handleDetachedRoomNavigation();
	houseZone _getCurrentHouseZoneIndex();

	std::optional<SDL_FPoint> m_focusPoint{};
	size_t m_currentWaypointIndex{};
	//std::vector<std::vector<SDL_FPoint>> m_manualWayPoints{};

	SDL_Point m_BathroomDestination{};

	int m_lastHouseZoneIndex{-1};


};

