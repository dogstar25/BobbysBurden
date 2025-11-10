#pragma once
#include "MobyDick.h"

class BBGhostBrainComponent :  public BrainComponent
{

public:

	BBGhostBrainComponent(Json::Value definitionJSON, GameObject* parent);

	void update() override;
	void postInit() override;

private:
	std::vector<std::shared_ptr<GameObject>> m_wayPoints;


	int _determineState();
	void _doPatrol();
	void _doEngage();
	void _doIdle();
	SDL_FPoint _getNextPatrolDestination();

	std::optional<SDL_FPoint> m_focusPoint{};
	size_t m_currentWaypointIndex{};
	std::vector<SDL_FPoint> m_manualWayPoints{};


};

