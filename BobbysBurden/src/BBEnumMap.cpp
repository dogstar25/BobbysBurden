#include "BBEnumMap.h"
#include "GameConstants.h"

BBEnumMap::BBEnumMap()
{

	//Custom Collision Tags
	addEnumItem("ContactTag::HEAVY_PARTICLE", ContactTag::HEAVY_PARTICLE);
	addEnumItem("ContactTag::LIGHT_PARTICLE", ContactTag::LIGHT_PARTICLE);
	addEnumItem("ContactTag::PLAYER_COLLISION", ContactTag::PLAYER_COLLISION);
	addEnumItem("ContactTag::PLAYER_TOUCH", ContactTag::PLAYER_TOUCH);
	addEnumItem("ContactTag::PLAYER_HITBOX", ContactTag::PLAYER_HITBOX);
	addEnumItem("ContactTag::WALL", ContactTag::WALL);
	addEnumItem("ContactTag::DOOR_TOUCH", ContactTag::DOOR_TOUCH);
	addEnumItem("ContactTag::DOOR_COLLISION", ContactTag::DOOR_COLLISION);
	addEnumItem("ContactTag::WARP_ENTRY", ContactTag::WARP_ENTRY);
	addEnumItem("ContactTag::STAIRS_TOUCH", ContactTag::STAIRS_TOUCH);
	addEnumItem("ContactTag::STAIRS_TOP_TOUCH", ContactTag::STAIRS_TOP_TOUCH);
	addEnumItem("ContactTag::STAIRS_BOTTOM_TOUCH", ContactTag::STAIRS_BOTTOM_TOUCH);
	addEnumItem("ContactTag::PUZZLE_OBJECT", ContactTag::PUZZLE_OBJECT);
	addEnumItem("ContactTag::INTERACTABLE_OBJECT", ContactTag::INTERACTABLE_OBJECT);
	addEnumItem("ContactTag::GAME_ITEM", ContactTag::GAME_ITEM);
	addEnumItem("ContactTag::DOOR_KNOB", ContactTag::DOOR_KNOB);

	
	//Custom Component Types
	addEnumItem("BOBBY_PLAYER_CONTROL_COMPONENT", ComponentTypes::BOBBY_PLAYER_CONTROL_COMPONENT);
	addEnumItem("BB_INTERFACE_COMPONENT", ComponentTypes::BB_INTERFACE_COMPONENT);
	addEnumItem("BB_STATE_COMPONENT", ComponentTypes::BB_STATE_COMPONENT);
	addEnumItem("BB_MASKED_OVERLAY_COMPONENT", ComponentTypes::BB_MASKED_OVERLAY_COMPONENT);

	//Custom Status/Context Item Types
	addEnumItem("StatusItemId::PLAYERS_HEART_COUNT", StatusItemId::PLAYERS_HEART_COUNT);

	//Custom actions
	addEnumItem("Actions::WARP", Actions::WARP);
	addEnumItem("Actions::OPEN", Actions::OPEN);
	addEnumItem("Actions::CLOSE", Actions::CLOSE);
	addEnumItem("Actions::ENTER", Actions::ENTER);
	addEnumItem("Actions::STAIRS_MOVE", Actions::STAIRS_MOVE);
	addEnumItem("Actions::EQUIP_LIGHT", Actions::EQUIP_LIGHT);

	//Traits
	addEnumItem("hiding_spot", TraitTag::hiding_spot);


}