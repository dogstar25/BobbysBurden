#include "BBColorMap.h"
#include "GameConstants.h"


BBColorMap::BBColorMap()
{


	addColor("Colors::NOCOLOR", Colors::NOCOLOR);
	addColor("Colors::ALPHA_100_COLOR", Colors::ALPHA_100_COLOR);
	addColor("Colors::ALPHA_1_COLOR", Colors::ALPHA_1_COLOR);
	
	//greens
	addColor("Colors::FOREST", Colors::FOREST);
	addColor("Colors::EMERALD", Colors::EMERALD);
	addColor("Colors::PARAKEET", Colors::PARAKEET);

	//reds
	addColor("Colors::WINE", Colors::WINE);
	addColor("Colors::GRAPE", Colors::GRAPE);

	//yellows
	addColor("Colors::GOLD", Colors::GOLD);
	addColor("Colors::CANDLE_LIGHT", Colors::CANDLE_LIGHT);
	addColor("Colors::COPPER", Colors::COPPER);

	//blues
	addColor("Colors::CYAN", Colors::CYAN);
	addColor("Colors::MARINE", Colors::MARINE);
	addColor("Colors::SAPPHIRE", Colors::SAPPHIRE);
	addColor("Colors::BLUEGREY", Colors::BLUEGREY);

	//Dark
	addColor("Colors::CHARCOAL", Colors::CHARCOAL);
	addColor("Colors::MIRKWOOD", Colors::MIRKWOOD);
	addColor("Colors::SLATE", Colors::SLATE);

	//BROWNS
	addColor("Colors::OAK", Colors::OAK);
	addColor("Colors::LIGHT_OAK", Colors::LIGHT_OAK);
}