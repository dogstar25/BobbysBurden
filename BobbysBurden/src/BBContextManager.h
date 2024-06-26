#pragma once

#include "MobyDick.h"
#include "GameConstants.h"


class BBContextManager : public ContextManager
{

public:
	//static MRContextManager& instance();
	BBContextManager() = default;
	SDL_Point currentHousePosition() { return m_currentHousePosition; }
	void setCurrentHousePosition(SDL_Point houseLocation) { m_currentHousePosition = houseLocation; }
	
	virtual bool saveSettings() override;
	virtual void loadSettings() override;

private:
	//Custom to BBGame
	SDL_Point m_currentHousePosition{ HousePositionTopLeftLocations::FRONT };



};

																																																																																																																	