#include "CutSceneClownArtMove.h"

extern std::unique_ptr<Game> game;



void CutSceneClownArtMove::run(Scene* scene)
{
	currentScene = scene;

	if (currentState == cutSceneState::IDLE) {

		start();
	}
	else if (currentState == cutSceneState::RUNNING) {

		update();

	}

}

void CutSceneClownArtMove::start()
{

	currentState = cutSceneState::RUNNING;
	int speed = 1;

	b2Vec2 moveDistanceTrajectory{0,-72};

	//Get the clown art object
	const auto& clownArtPicture = currentScene->getFirstGameObjectByType("WALL_ART_CLOWN_1");
	if (clownArtPicture.has_value()) {

		_clownArtObject = clownArtPicture.value();

		_targetLocation = { 
			_clownArtObject.lock()->getCenterPosition().x + moveDistanceTrajectory.x, 
			_clownArtObject.lock()->getCenterPosition().y + moveDistanceTrajectory.y 
		};

		moveDistanceTrajectory.Normalize();

		const auto& physicsComponent = _clownArtObject.lock()->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);
		physicsComponent->applyMovement(speed, { moveDistanceTrajectory.x,moveDistanceTrajectory.y});


	}
	

}

void CutSceneClownArtMove::update()
{

	//check to see if the picture has finished the move
	if (_targetLocation) {

		auto distance = util::calculateDistance(_clownArtObject.lock()->getCenterPosition(), _targetLocation.value());
		if (distance < 1) {

				const auto& physicsComponent = _clownArtObject.lock()->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);
				physicsComponent->setLinearVelocity({ 0,0 });

				end();

		}
	}

}

void CutSceneClownArtMove::end()
{
	SDL_Event event;

	//Create the event that will trigger the end of the scene to the sceneManager
	util::sendSceneEvent(SCENE_ACTION_RELEASE_DIRECT);

}

