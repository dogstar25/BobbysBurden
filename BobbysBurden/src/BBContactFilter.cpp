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
	m_contactMasks[PLAYER_TOUCH].flip();

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

}

bool BBContactFilter::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB)
{
	//Call base function
	return ContactFilter::ShouldCollide(fixtureA, fixtureB);


}
