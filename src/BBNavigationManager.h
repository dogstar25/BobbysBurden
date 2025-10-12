#pragma once
#include "MobyDick.h"

class BBNavigationManager : public NavigationManager
{

public:

	BBNavigationManager();

	virtual void buildNavigationMapItem(GameObject* gameObject, Scene* scene) override;
	virtual void updateNavigationMap() override;

	void buildNavigationMap();//This nav map is built manually, not using the levelmanager

private:

	std::vector<SDL_FPoint> m_navigationPoints{};
	//std::vector<int> validYAxisNav = { 141, 152, 161, 130};

	
	bool _isPointInValidNavList(SDL_Point navPoint);

};

