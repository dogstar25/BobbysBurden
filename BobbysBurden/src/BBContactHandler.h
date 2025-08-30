#pragma once

#include "MobyDick.h"

class GameObject;


class BBContactHandler : public ContactHandler
{
public:

	BBContactHandler() {};

	void virtual handleContacts(const b2WorldId physicsWorldId) override;
	

private:

	void _actor_warpEntry(GameObject*, GameObject*, const b2Vec2 contactPoint[]);
	
};

