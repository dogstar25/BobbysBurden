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
	addEnumItem("ContactTag::INTERACTABLE_OBJECT", ContactTag::INTERACTABLE_OBJECT);
	addEnumItem("ContactTag::INVENTORY_HOLDER", ContactTag::INVENTORY_HOLDER);
	addEnumItem("ContactTag::INVENTORY_ITEM", ContactTag::INVENTORY_ITEM);

	
	//Custom Component Types
	addEnumItem("BOBBY_PLAYER_CONTROL_COMPONENT", ComponentTypes::BOBBY_PLAYER_CONTROL_COMPONENT);
	addEnumItem("BB_INTERFACE_COMPONENT", ComponentTypes::BB_INTERFACE_COMPONENT);
	addEnumItem("BB_STATE_COMPONENT", ComponentTypes::BB_STATE_COMPONENT);

	//Custom Status/Context Item Types
	addEnumItem("StatusItemId::PLAYERS_HEART_COUNT", StatusItemId::PLAYERS_HEART_COUNT);

	//Custom actions
	addEnumItem("Actions::WARP", Actions::WARP);
	addEnumItem("Actions::OPEN", Actions::OPEN);
	addEnumItem("Actions::CLOSE", Actions::CLOSE);
	addEnumItem("Actions::ENTER", Actions::ENTER);
	addEnumItem("Actions::STAIRS_MOVE", Actions::STAIRS_MOVE);

	//Traits
	addEnumItem("door", TraitTag::door);
	addEnumItem("door_entry", TraitTag::door_entry);
	addEnumItem("hiding_spot", TraitTag::hiding_spot);
	addEnumItem("receptacle", TraitTag::receptacle);
	addEnumItem("shelf", TraitTag::shelved);

	//GameObject States
	m_enumMap["GameObjectState::DEPLOYED"] = GameObjectState::DEPLOYED;
	m_enumMap["GameObjectState::CONCEALED"] = GameObjectState::CONCEALED;
	m_enumMap["GameObjectState::IMPASSABLE"] = GameObjectState::IMPASSABLE;
	m_enumMap["GameObjectState::ITEM_OBTAINABLE"] = GameObjectState::ITEM_OBTAINABLE;
	m_enumMap["GameObjectState::ITEM_LOOSE"] = GameObjectState::ITEM_LOOSE;
	m_enumMap["GameObjectState::ITEM_STORED_ENCLOSED"] = GameObjectState::ITEM_STORED_ENCLOSED;
	m_enumMap["GameObjectState::ITEM_STORED_OPEN"] = GameObjectState::ITEM_STORED_OPEN;
	m_enumMap["GameObjectState::ITEM_STORED_PLAYER"] = GameObjectState::ITEM_STORED_PLAYER;
	m_enumMap["GameObjectState::IDLE_RIGHT"] = GameObjectState::IDLE_RIGHT;
	m_enumMap["GameObjectState::IDLE_LEFT"] = GameObjectState::IDLE_LEFT;
	m_enumMap["GameObjectState::IDLE_UP"] = GameObjectState::IDLE_UP;
	m_enumMap["GameObjectState::IDLE_DOWN"] = GameObjectState::IDLE_DOWN;
	m_enumMap["GameObjectState::WALK_RIGHT"] = GameObjectState::WALK_RIGHT;
	m_enumMap["GameObjectState::WALK_LEFT"] = GameObjectState::WALK_LEFT;
	m_enumMap["GameObjectState::WALK_UP"] = GameObjectState::WALK_UP;
	m_enumMap["GameObjectState::WALK_DOWN"] = GameObjectState::WALK_DOWN;
	m_enumMap["GameObjectState::RUN_RIGHT"] = GameObjectState::RUN_RIGHT;
	m_enumMap["GameObjectState::RUN_LEFT"] = GameObjectState::RUN_LEFT;
	m_enumMap["GameObjectState::RUN_UP"] = GameObjectState::RUN_UP;
	m_enumMap["GameObjectState::RUN_DOWN"] = GameObjectState::RUN_DOWN;


}