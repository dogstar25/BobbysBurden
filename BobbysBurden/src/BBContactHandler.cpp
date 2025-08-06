#include "BBContactHandler.h"
#include "BBContextManager.h"
#include "GameConstants.h"
#include "particleEffects/GameParticleEffects.h"
#include "components/BobbyPlayerControlComponent.h"

extern std::unique_ptr<Game> game;



void BBContactHandler::_actor_warpEntry(GameObject* interactingObject, GameObject* warpEntry, const b2Vec2 contactPoint[])
{

	const auto& physicsComponent = interactingObject->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);

	//build name for the warp exit object 
	std::string warpExitName = warpEntry->name() + "_EXIT";

	//Find this warp interactions exit
	const auto& exit = interactingObject->parentScene()->getFirstGameObjectByName(warpExitName);
	if (exit.has_value()) {

		//Get location and use it as warp destination
		b2Vec2 exitLocation = { exit.value()->getCenterPosition().x, exit.value()->getCenterPosition().y };
		util::toBox2dPoint(exitLocation);
		physicsComponent->setChangePositionPosition(exitLocation);

	}

}

void BBContactHandler::handleContacts(const b2WorldId physicsWorldId)
{


	b2ContactEvents contactEvents = b2World_GetContactEvents(physicsWorldId);

	for (int i = 0; i < contactEvents.beginCount; ++i) {

		const b2ContactBeginTouchEvent& event = contactEvents.beginEvents[i];

		//Get Shape User Data which is the contact collision info
		//This represents the gameObject's potential individual physical parts
		void* shapeUserDataA = b2Shape_GetUserData(event.shapeIdA);
		void* shapeUserDataB = b2Shape_GetUserData(event.shapeIdB);

		ContactDefinition* contactDefinitionA = reinterpret_cast<ContactDefinition*>(shapeUserDataA);
		ContactDefinition* contactDefinitionB = reinterpret_cast<ContactDefinition*>(shapeUserDataB);
		int contactTagA = contactDefinitionA->contactTag;
		int contactTagB = contactDefinitionB->contactTag;

		//Get BodyId and Body User Data
		//This represents the gameObject Itself usually
		b2BodyId bodyIdA = b2Shape_GetBody(event.shapeIdA);
		b2BodyId bodyIdB = b2Shape_GetBody(event.shapeIdB);
		void* bodyUserDataA = b2Body_GetUserData(bodyIdA);
		void* bodyUserDataB = b2Body_GetUserData(bodyIdB);

		//Get the GameObjects associated with these bodies
		GameObject* contactA = reinterpret_cast<GameObject*>(bodyUserDataA);
		GameObject* contactB = reinterpret_cast<GameObject*>(bodyUserDataB);

		// If the contact point count is zero, which apparently is possible in box2d v3 then dont do anything, otherwise, 
		// pass in both contact points and let the specific scenario use them as needed
		if (event.manifold.pointCount  <=0 ) {

			return;
		}

		////////////////////////////////////
		// Player -  Warp Entry
		//////////////////////////////////
		if ((contactTagA == ContactTag::PLAYER_COLLISION && contactTagA == ContactTag::WARP_ENTRY) ||
			(contactTagB == ContactTag::PLAYER_COLLISION && contactTagB == ContactTag::WARP_ENTRY)) {

			if (contactTagA == ContactTag::PLAYER_COLLISION) {
				_actor_warpEntry(contactA, contactB, &event.manifold.points->point);
			}
			else {
				_actor_warpEntry(contactA, contactB, &event.manifold.points->point);
			}
		}

	}

}






