#include "BBNavigationManager.h"

BBNavigationManager::BBNavigationManager()
{

	m_navigationPoints = {

		//attic floor
		{1,2},

		//Top floor
		{16,141},{17,141},{18,141},{19,141},{20,141},{21,141},{22,141},{23,141},{24,141},{25,141},{26,141},{27,141},{28,141},{29,141},{30,141},{31,141},{32,141},
		{33,141},{34,141},{35,141},{36,141},{37,141},{38,141},{39,141},{40,141},{41,141},{42,141},{44,141},{45,141},{46,141},{47,141},{48,141},{49,141},{50,141},
		{51,141},{52,141},{53,141},{54,141},{55,141},{56,141},{57,141},{58,141},{59,141},

		//Bottom Floor
		{16,152},{17,152},{18,152},{19,152},{20,152},{21,152},{22,152},{23,152},{24,152},{25,152},{26,152},{27,152},{28,152},{29,152},{30,152},{31,152},{32,152},
		{33,152},{34,152},{35,152},{36,152},{37,152},{38,152},{39,152},{40,152},{41,152},{42,152},{44,152},{45,152},{46,152},{47,152},{48,152},{49,152},{50,152},
		{51,152},{52,152},{53,152},{54,152},{55,152},{56,152},{57,152},{58,152},{59,152},

		//Cellar
		//{0,0},

		//Main stairs
		{40,142},{40,143},{40,144},{40,145},{40,146},{40,147},{40,148},{40,149},{40,150},{40,151},
		 
		//Bobbys bathroom
		{151,19},{152,19},{153,19},{154,19},{155,19},{156,19},{157,19},{158,19},{159,19},{160,19},{161,19},{162,19},{163,19},{164,19},{165,19},{166,19},{167,19},
		{168,19},{169,19},

	};

}

void BBNavigationManager::buildNavigationMap()
{

	//m_navigationMap.resize(width, std::vector<NavigationMapItem>(height));

	//Initialize all to false
	for (auto& row : m_navigationMap) {
		for (auto& item : row) {
			item.passable = false;
		}
	}

	//Add all of our hardcoded nav points
	for (const auto& point : m_navigationPoints) {

		m_navigationMap[point.x][point.y].passable = true;

	}




}

void BBNavigationManager::updateNavigationMap()
{


}