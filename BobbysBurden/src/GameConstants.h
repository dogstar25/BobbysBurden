 #pragma once
#include "MobyDick.h"


namespace Colors {

	inline SDL_Color NOCOLOR = { 0, 0, 0, 0 };
	inline SDL_Color ALPHA_100_COLOR = { 255, 255, 255, 100 };
	inline SDL_Color ALPHA_1_COLOR = { 255, 255, 255, 1 };

	//green
	inline SDL_Color FOREST = { 10, 75, 10, 255 };
	inline SDL_Color EMERALD = { 10, 125, 10, 255 };
	inline SDL_Color PARAKEET = { 38, 195, 15, 255 };
	
	//red
	inline SDL_Color WINE = { 127, 0, 34, 255 };
	inline SDL_Color GRAPE = { 200, 0, 255, 255 };

	//yellow
	inline SDL_Color GOLD = { 173, 167, 54, 255 };
	inline SDL_Color CANDLE_LIGHT = { 238, 235, 175, 255 };
	

	//blue
	inline SDL_Color MARINE = { 50, 147, 196, 255 };
	inline SDL_Color SAPPHIRE = { 113, 197, 219, 255 };
	inline SDL_Color BLUEGREY = { 135, 192, 202, 255 };

	//grey / dark
	inline SDL_Color CHARCOAL = { 25, 25, 25, 255 };
	inline SDL_Color MIRKWOOD = { 39, 52, 39, 255 };
	inline SDL_Color SLATE = { 11, 14, 51, 255 };

	//Browns
	inline SDL_Color OAK = { 111, 70, 42, 255 };
	inline SDL_Color LIGHT_OAK = { 145, 103, 64, 255 };


}

namespace HousePositionTopLeftLocations {

	inline SDL_Point FRONT = { 0, 110 };
	inline SDL_Point BACK = { 135, 22 };

}

namespace ContactTag {
	
	inline constexpr int SMOKE_PARTICLE = 10;
	inline constexpr int NAVIGATION_POINT = 11;
	inline constexpr int HEAVY_PARTICLE = 12;
	inline constexpr int LIGHT_PARTICLE = 13;
	inline constexpr int PLAYER_TOUCH = 14;
	inline constexpr int PLAYER_COLLISION = 15;
	inline constexpr int PLAYER_HITBOX = 16;
	inline constexpr int WALL = 17;
	inline constexpr int DOOR_TOUCH = 18;
	inline constexpr int DOOR_COLLISION = 19;
	inline constexpr int WARP_ENTRY = 20;
	inline constexpr int STAIRS_TOUCH = 21;
	inline constexpr int STAIRS_TOP_TOUCH = 22;
	inline constexpr int STAIRS_BOTTOM_TOUCH = 23;
	inline constexpr int PUZZLE_OBJECT = 24;
	inline constexpr int INTERACTABLE_OBJECT = 26;
	inline constexpr int GAME_ITEM = 28;
	inline constexpr int DOOR_KNOB = 29;
	inline constexpr int FRIGHTING_OBJECT = 30;
	inline constexpr int BED_STAIRS = 31;
	inline constexpr int HIDING_SPOT = 32;
	

}

namespace ComponentTypes {

	inline constexpr int BOBBY_PLAYER_CONTROL_COMPONENT = ComponentTypes::LAST_BASE_COMPONENT + 1;
	inline constexpr int BB_INTERFACE_COMPONENT = ComponentTypes::LAST_BASE_COMPONENT + 2;
	inline constexpr int BB_STATE_COMPONENT = ComponentTypes::LAST_BASE_COMPONENT + 3;
	inline constexpr int BB_MASKED_OVERLAY_COMPONENT = ComponentTypes::LAST_BASE_COMPONENT + 4;
	inline constexpr int BB_ENVIRONMENT_COMPONENT = ComponentTypes::LAST_BASE_COMPONENT + 5;
	inline constexpr int BB_GHOST_BRAIN_COMPONENT = ComponentTypes::LAST_BASE_COMPONENT + 6;
	

}

namespace BrainState {

	inline constexpr auto UNDISCOVERED = 20;
	inline constexpr auto FIRST_DISCOVERED = 21;

}

namespace TraitTag {

	//Custom traits
	inline constexpr int hiding_spot = 75;
	
}

namespace Actions {
	inline constexpr int STAIRS_MOVE = 30;
	inline constexpr int EQUIP_LIGHT = 31;
	inline constexpr int DEPLOY = 32;
	inline constexpr int UNDEPLOY = 33;
	inline constexpr int APPLY_SCARE = 34;
	inline constexpr int REMOVE_SCARE = 35;

}

namespace StatusItemId {
	inline constexpr int HOUSE_POSITION = 10;
	inline constexpr int PLAYERS_HEART_COUNT = 11;
	
	
};

enum class LightningLayor {
	BACK,
	MIDDLE,
	FRONT
};




