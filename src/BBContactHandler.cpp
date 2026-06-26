#include "BBContactHandler.h"
#include "BBContextManager.h"
#include "GameConstants.h"
#include "particleEffects/GameParticleEffects.h"
#include "components/BobbyPlayerControlComponent.h"
#include "cutScenes/BBCutSceneCaught.h"

//extern std::unique_ptr<Game> game;



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

		const auto& physicsComponent = interactingObject->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);

		b2Body_SetTransform(physicsComponent->physicsBodyId(), exitLocation, b2Body_GetRotation(physicsComponent->physicsBodyId()));


	}

}

void BBContactHandler::_actor_ghostCaughtBobby(GameObject* ghost, GameObject* bobby)
{

	// Don't re-trigger if a cutscene is already running
	if (SceneManager::instance().currentScene().cutScene().has_value()) {
		return;
	}

	SceneManager::instance().directScene("BBCutSceneCaught");

}

void BBContactHandler::handleSensors(const b2WorldId physicsWorldId)
{

	// Base class updates touchingObjects for all sensor overlaps
	ContactHandler::handleSensors(physicsWorldId);

	b2SensorEvents sensorEvents = b2World_GetSensorEvents(physicsWorldId);

	for (int i = 0; i < sensorEvents.beginCount; ++i) {

		const b2SensorBeginTouchEvent& event = sensorEvents.beginEvents[i];

		void* sensorShapeUserData = b2Shape_GetUserData(event.sensorShapeId);
		void* visitorShapeUserData = b2Shape_GetUserData(event.visitorShapeId);

		ContactDefinition* sensorContactDef = reinterpret_cast<ContactDefinition*>(sensorShapeUserData);
		ContactDefinition* visitorContactDef = reinterpret_cast<ContactDefinition*>(visitorShapeUserData);

		if (!sensorContactDef || !visitorContactDef) {
			continue;
		}

		int sensorTag = sensorContactDef->contactTag;
		int visitorTag = visitorContactDef->contactTag;

		//////////////////////////////////////
		// Ghost Touch + Bobby Collision
		//////////////////////////////////////
		if (sensorTag == ContactTag::GHOST_TOUCH && visitorTag == ContactTag::PLAYER_COLLISION) {

			b2BodyId ghostBodyId = b2Shape_GetBody(event.sensorShapeId);
			b2BodyId bobbyBodyId = b2Shape_GetBody(event.visitorShapeId);

			GameObject* ghost = reinterpret_cast<GameObject*>(b2Body_GetUserData(ghostBodyId));
			GameObject* bobby = reinterpret_cast<GameObject*>(b2Body_GetUserData(bobbyBodyId));

			_actor_ghostCaughtBobby(ghost, bobby);

		}

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






