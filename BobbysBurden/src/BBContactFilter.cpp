#include "BBContactFilter.h"
#include "GameConstants.h"

BBContactFilter::BBContactFilter()
{

	using namespace ContactTag;

	//LEVEL_CAGE
	m_contactMasks[LEVEL_CAGE].reset();
	m_contactMasks[LEVEL_CAGE].set(PLAYER_COLLISION);

	//PLAYER_COLLISION
	m_contactMasks[PLAYER_COLLISION].reset();
	m_contactMasks[PLAYER_COLLISION].set(GENERAL_SOLID);
	m_contactMasks[PLAYER_COLLISION].set(WALL);
	m_contactMasks[PLAYER_COLLISION].set(HEAVY_PARTICLE);
	m_contactMasks[PLAYER_COLLISION].set(LEVEL_CAGE);
	m_contactMasks[PLAYER_COLLISION].set(PLAYER_COLLISION);
	m_contactMasks[PLAYER_COLLISION].set(DOOR_COLLISION);
	m_contactMasks[PLAYER_COLLISION].set(DOOR_TOUCH);
	m_contactMasks[PLAYER_COLLISION].set(WARP_ENTRY);
	m_contactMasks[PLAYER_COLLISION].set(STAIRS_TOUCH);
	
	//PLAYER_TOUCH
	m_contactMasks[PLAYER_TOUCH].reset();
	m_contactMasks[PLAYER_TOUCH].set(INTERACTABLE_OBJECT);
	m_contactMasks[PLAYER_TOUCH].set(GAME_ITEM);
	m_contactMasks[PLAYER_TOUCH].set(PUZZLE_OBJECT);
	m_contactMasks[PLAYER_TOUCH].set(INTERACTABLE_OBJECT);
	

	//PLAYER_HITBOX
	m_contactMasks[PLAYER_HITBOX].reset();
	m_contactMasks[PLAYER_HITBOX].set(HEAVY_PARTICLE);


	//WALL
	m_contactMasks[WALL].reset();
	m_contactMasks[WALL].set(GENERAL_SOLID);
	m_contactMasks[WALL].set(HEAVY_PARTICLE);
	m_contactMasks[WALL].set(PLAYER_COLLISION);
	m_contactMasks[WALL].set(WALL);

	//DOOR Collision
	m_contactMasks[DOOR_COLLISION].reset();
	m_contactMasks[DOOR_COLLISION].set(PLAYER_COLLISION);

	//DOOR TOUCH
	m_contactMasks[DOOR_TOUCH].reset();
	m_contactMasks[DOOR_TOUCH].set(PLAYER_COLLISION);

	//WARP ENTRY
	m_contactMasks[WARP_ENTRY].reset();
	m_contactMasks[WARP_ENTRY].set(PLAYER_COLLISION);

	//Stairs Touch
	m_contactMasks[STAIRS_TOUCH].set(PLAYER_COLLISION);

	//Interactable Objects
	m_contactMasks[INTERACTABLE_OBJECT].reset();
	m_contactMasks[INTERACTABLE_OBJECT].set(PLAYER_TOUCH);
	m_contactMasks[INTERACTABLE_OBJECT].set(GAME_ITEM);

	//Heavy Particle
	m_contactMasks[HEAVY_PARTICLE].reset();
	m_contactMasks[HEAVY_PARTICLE].set(PLAYER_COLLISION);
	m_contactMasks[HEAVY_PARTICLE].set(WALL);

	//Game Item
	m_contactMasks[GAME_ITEM].reset();
	m_contactMasks[GAME_ITEM].set(PLAYER_TOUCH);
	m_contactMasks[GAME_ITEM].set(WALL);
	m_contactMasks[GAME_ITEM].set(INTERACTABLE_OBJECT);
	m_contactMasks[GAME_ITEM].set(PUZZLE_OBJECT);

	//Puzzle Object
	m_contactMasks[PUZZLE_OBJECT].reset();
	m_contactMasks[PUZZLE_OBJECT].set(PLAYER_TOUCH);
	m_contactMasks[PUZZLE_OBJECT].set(GAME_ITEM);

}

bool BBContactFilter::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB)
{
	//Call base function
	return ContactFilter::ShouldCollide(fixtureA, fixtureB);


}
