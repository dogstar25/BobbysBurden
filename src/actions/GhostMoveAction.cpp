#include "GhostMoveAction.h"



//#include "GameObject.h"


void GhostMoveAction::perform(b2Vec2 trajectory)
{

	const auto& physicsComponent = m_parent->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);
	const auto& stateComponent = m_parent->getComponent<StateComponent>(ComponentTypes::STATE_COMPONENT);

	b2Vec2 linearVelocity = physicsComponent->linearVelocity();
	const float ax = std::fabs(linearVelocity.x);
	const float ay = std::fabs(linearVelocity.y);

	linearVelocity *= 10;

	if (ax < .01 && ay < .01) {

		stateComponent->addState(GameObjectState::IDLE);
	}
	else if (linearVelocity.x < 1 && ax > .01 ) {

		stateComponent->addState(GameObjectState::WALK_LEFT);
	}
	else if (linearVelocity.x > 1 && ax > .01) {

		stateComponent->addState(GameObjectState::WALK_RIGHT);
	}
	else if (linearVelocity.y < 1 && ay > .01) {

		stateComponent->addState(GameObjectState::WALK_UP);
	}
	else if (linearVelocity.y > 1 && ay > .01) {

		stateComponent->addState(GameObjectState::WALK_DOWN);
	}


	DefaultMoveAction::perform(trajectory);

}

