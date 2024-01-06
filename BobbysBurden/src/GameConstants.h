 #pragma once
#include "MobyDick.h"


/*
* 
* Layer Guide
* 
BACKGROUND_5	backgroundBricks,		
BACKGROUND_4
BACKGROUND_3
BACKGROUND_2
BACKGROUND_1
MAIN			player
FOREGROUND_1
FOREGROUND_2
FOREGROUND_3
FOREGROUND_4	foregroundBricks
FOREGROUND_5	exterior
GUI,
ABSTRACT,
GRID_DISPLAY,
*/

namespace Colors {

	inline SDL_Color NOCOLOR = { 0, 0, 0, 0 };
	inline SDL_Color ALPHA_100_COLOR = { 255, 255, 255, 100 };

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

	//grey / dark
	inline SDL_Color CHARCOAL = { 25, 25, 25, 255 };
	inline SDL_Color MIRKWOOD = { 39, 52, 39, 255 };
	inline SDL_Color SLATE = { 11, 14, 51, 255 };

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
	inline constexpr int PUZZLE = 24;
	inline constexpr int PUZZLE_PIECE = 25;
	inline constexpr int INTERACTABLE_OBJECT = 26;
	inline constexpr int INVENTORY_HOLDER = 27;
	inline constexpr int INVENTORY_ITEM = 28;
	

}

namespace GameObjectState {

	inline constexpr int DEPLOYED = 50;
	inline constexpr int CONCEALED = 51;
	inline constexpr int IMPASSABLE = 52;
	inline constexpr int ITEM_OBTAINABLE = 53;
	inline constexpr int ITEM_LOOSE = 54;
	inline constexpr int ITEM_STORED_ENCLOSED = 55;
	inline constexpr int ITEM_STORED_OPEN = 56;
	inline constexpr int ITEM_STORED_PLAYER = 57;
	inline constexpr int IDLE_RIGHT = 58;
	inline constexpr int IDLE_LEFT = 59;
	inline constexpr int IDLE_UP = 60;
	inline constexpr int IDLE_DOWN = 61;
	inline constexpr int WALK_RIGHT = 62;
	inline constexpr int WALK_LEFT = 63;
	inline constexpr int WALK_UP = 64;
	inline constexpr int WALK_DOWN = 65;
	inline constexpr int RUN_RIGHT = 66;
	inline constexpr int RUN_LEFT = 67;
	inline constexpr int RUN_UP = 68;
	inline constexpr int RUN_DOWN = 69;

};

namespace ComponentTypes {

	inline constexpr int BOBBY_PLAYER_CONTROL_COMPONENT = ComponentTypes::LAST_BASE_COMPONENT + 1;
	inline constexpr int BB_INTERFACE_COMPONENT = ComponentTypes::LAST_BASE_COMPONENT + 2;
	inline constexpr int BB_STATE_COMPONENT = ComponentTypes::LAST_BASE_COMPONENT + 3;

}

namespace BrainState {

	inline constexpr auto FOLLOW = 20;

}

namespace TraitTag {

	//Custom traits
	inline constexpr int door_entry = 30;
	inline constexpr int door = 31;
	inline constexpr int hiding_spot = 32;
	inline constexpr int receptacle = 33;			//Can be open or closed and hold items
	
}

namespace Actions {
	inline constexpr int STAIRS_MOVE = 30;

}

namespace StatusItemId {
	inline constexpr int PLAYERS_HEART_COUNT = 10;
	
};


