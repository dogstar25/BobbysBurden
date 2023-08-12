#pragma once

#include "MobyDick.h"

class GameObject;


class BBContactListener : public ContactListener
{
public:

	BBContactListener() {};

	void BeginContact(b2Contact*) override;
	void EndContact(b2Contact*) override;

	void virtual handleContact(b2Contact* contact, b2Vec2 contactPoint) override;

private:

	void _actor_warpEntry(GameObject*, GameObject*, b2Vec2 contactPoint);
	void _puzzle_puzzlePiece(GameObject*, GameObject*, b2Vec2 contactPoint);
	void _inventoryItem_inventoryHolder(GameObject*, GameObject*, b2Vec2 contactPoint);
	
};

