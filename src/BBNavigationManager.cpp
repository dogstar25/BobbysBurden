#include "BBNavigationManager.h"

BBNavigationManager::BBNavigationManager()
{

	m_navigationPoints = {

		//Top floor
		{16,139},{17,139},{18,139},{19,139},{20,139},{21,139},{22,139},{23,139},{24,139},{25,139},{26,139},{27,139},{28,139},{29,139},{30,139},{31,139},{32,139},
		{33,139},{34,139},{35,139},{36,139},{37,139},{38,139},{39,139},{40,139},{41,139},{42,139},{43,139},{44,139},{45,139},{46,139},{47,139},{48,139},{49,139},{50,139},
		{51,139},{52,139},{53,139},{54,139},{55,139},{56,139},{57,139},{58,139},{59,139},{17,140}, {17,141},

		//Bottom Floor
		{16,150},{17,150},{18,150},{19,150},{20,150},{21,150},{22,150},{23,150},{24,150},{25,150},{26,150},{27,150},{28,150},{29,150},{30,150},{31,150},{32,150},
		{33,150},{34,150},{35,150},{36,150},{37,150},{38,150},{39,150},{40,150},{41,150},{42,150},{43,150},{44,150},{45,150},{46,150},{47,150},{48,150},{49,150},{50,150},
		{51,150},{52,150},{53,150},{54,150},{55,150},{56,150},{57,150},{58,150},{59,150},

		//Cellar
		//{0,0},

		//Main stairs
		{40,139},{40,140},{40,141},{40,142},{40,143},{40,144},{40,145},{40,146},{40,147},{40,148},{40,149},{40,150},

		//Path to attic
		{36,138},{36,137},{36,136},{36,135},{36,134},{37,134},{38,134},{38,133},{38,132},{38,131},{38,130},{38,129},{38,128},

		//attic floor
		{37,128},{36,128},{35,128},{34,128},{33,128},{32,128},{31,128},{30,128},{29,128},{28,128},{27,128},{26,128},{25,128},{24,128},{23,128},{22,128},{21,128},
		{20,128},{19,128},


		//Bobbys bathroom
		{ 29,72 },{30,72},{31,72},{32,72},{33,72},{34,72},{35,72},{36,72},{37,72},{38,72},{39,72},{40,72},{41,72},{42,72},{43,72},{44,72},{45,72},
		{42,75}, {42,74},{42,73}, {42,72}

	};

}

void BBNavigationManager::buildNavigationMap()
{

	//m_navigationMap.resize(width, std::vector<NavigationMapItem>(height));

	//Initialize all to false
	for (auto& row : m_navigationMap) {
		for (auto& item : row) {
			//todd temp
			//item.passable = true;
			item.passable = false;
		}
	}

	//Add all of our hardcoded nav points
	for (const auto& point : m_navigationPoints) {

		m_navigationMap[static_cast<int>(point.x)][static_cast<int>(point.y)].passable = true;

	}

}

void BBNavigationManager::updateNavigationMap()
{

	//NavigationManager::updateNavigationMap();

}

void BBNavigationManager::buildNavigationMapItem(GameObject* gameObject, Scene* scene)
{

	//NavigationMapItem navigationMapItem{};

	////This is a possible impasse
	//if (gameObject->hasTrait(TraitTag::impasse) ||
	//	gameObject->hasTrait(TraitTag::conditional_impasse) ||
	//	gameObject->hasTrait(TraitTag::complex_impasse))
	//{

	//	//Find this objects shared_ptr so we can store the weak_ptr of it here
	//	auto gameObjectSharedPtr = scene->getGameObject(gameObject->id()).value();

	//	navigationMapItem.gameObject = gameObjectSharedPtr;

	//	//If this is impasse, then it will always be so set it now so that the 
	//	//the navigationComponent will work on the first pass
	//	if (gameObject->hasTrait(TraitTag::impasse)) {
	//		navigationMapItem.passable = false;
	//	}

	//	//Add the initial navigationMapItem to the collection
	//	m_navigationMap[(int)gameObject->getOriginalTilePosition().x][(int)gameObject->getOriginalTilePosition().y] = navigationMapItem;

	//}
	//else {

	//	navigationMapItem.passable = true;
	//	m_navigationMap[(int)gameObject->getOriginalTilePosition().x][(int)gameObject->getOriginalTilePosition().y] = navigationMapItem;

	//}

}
