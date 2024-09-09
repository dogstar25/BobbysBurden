#include "BobbyPlayerControlComponent.h"
#include "../GameConstants.h"

extern std::unique_ptr<Game> game;

BobbyPlayerControlComponent::BobbyPlayerControlComponent(Json::Value componentJSON, GameObject* parent)
	: PlayerControlComponent(componentJSON, parent)
{

}

BobbyPlayerControlComponent::~BobbyPlayerControlComponent()
{

}

void BobbyPlayerControlComponent::postInit()
{

}

void BobbyPlayerControlComponent::update()
{

	//ALways ensure that bobby is upright
	const auto& playerPhysics = parent()->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);
	playerPhysics->setAngle(0.);

	_handleMovement();

}

void BobbyPlayerControlComponent::_handleMovement()
{
	int mouseX = 0, mouseY = 0;
	int direction = 0, strafe = 0;

	//convenience reference to outside component(s)
	const auto& actionComponent = parent()->getComponent<ActionComponent>(ComponentTypes::ACTION_COMPONENT);
	const auto& stateComponent = parent()->getComponent<StateComponent>(ComponentTypes::STATE_COMPONENT);

	//Handle Keyboard related movement
	const uint8_t* currentKeyStates = SDL_GetKeyboardState(NULL);

	//Touching stairs
	if (parent()->isTouchingByTrait(TraitTag::vertical_movement_zone)) {

		stateComponent->addState(GameObjectState::ON_VERTICAL_MOVEMENT);
		//_applyStairWalkingSettings();
	}
	else {
		stateComponent->removeState(GameObjectState::ON_VERTICAL_MOVEMENT);
		//_removeStairWalkingSettings();
	}

	if (currentKeyStates[SDL_SCANCODE_W])
	{
		direction = -1;
	}
	if (currentKeyStates[SDL_SCANCODE_S])
	{
		direction = 1;

	}

	if (currentKeyStates[SDL_SCANCODE_A])
	{
		strafe = -1;
	}
	if (currentKeyStates[SDL_SCANCODE_D])
	{
		strafe = 1;
	}
	
	//Sprint
	if (currentKeyStates[SDL_SCANCODE_LSHIFT])
	{

		//const auto& action = actionComponent->getAction(ACTION_SPRINT);
		//action->perform(parent(), direction, strafe);
		//m_state.set(PlayerState::sprinting);
	}
	else {

		const auto& moveAction = actionComponent->getAction(Actions::MOVE);
		moveAction->perform(direction, strafe);


	}


	//Handle Mouse related movement
	//const uint32_t currentMouseStates = SDL_GetRelativeMouseState(&mouseX, &mouseY);
	//float angularVelocity = mouseX * game->contextMananger()->getMouseSensitivity();

	//ImGui::Begin("mouse2");
	//ImGui::Value("X", mouseX);
	//ImGui::Value("Y", mouseY);

	//ImGui::End();


}


void BobbyPlayerControlComponent::_applyStairWalkingSettings()
{
	const auto& playerPhysics = parent()->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);
	const auto& playerVitality = parent()->getComponent<VitalityComponent>(ComponentTypes::VITALITY_COMPONENT);

	playerPhysics->setGravityScale(0);
	playerPhysics->setLinearDamping(100);
	playerPhysics->setAngularDamping(100);
	playerVitality->setSpeed(5);

}

void BobbyPlayerControlComponent::_removeStairWalkingSettings()
{

	const auto& playerPhysics = parent()->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);
	const auto& playerVitality = parent()->getComponent<VitalityComponent>(ComponentTypes::VITALITY_COMPONENT);

	playerPhysics->setGravityScale(15);
	playerPhysics->setLinearDamping(1);
	playerPhysics->setAngularDamping(1);
	playerVitality->setSpeed(3);

}

//void BobbyPlayerControlComponent::_handleActions()
//{
//	//Get the current mouse state
//	int mouseX, mouseY;
//	auto mouseButtons = SDL_GetMouseState(&mouseX, &mouseY);
//
//	if (SceneManager::instance().playerInputEvents().empty() == false) {
//		//convenience reference to outside component(s)
//		const auto& actionComponent = parent()->getComponent<ActionComponent>(ComponentTypes::ACTION_COMPONENT);
//
//		std::shared_ptr<Action> action{};
//
//		for (auto& inputEvent : SceneManager::instance().playerInputEvents())
//		{
//			//std::optional<Action> playerAction{};
//			SDL_Scancode keyScanCode = SDL_GetScancodeFromKey(inputEvent.event.key.keysym.sym);
//
//
//
//			//
//			// What if we determine here if the mouse clicked or a key was hit that is NOT movement related
//			// then we let it pass so that the various objects with interface components can catch it and do whatever
//			//
//			//OR
//			//
//			//If a mouse click then we see if it clicked an object and we call thats objects onClick
//			//		The onClick would be smart enought to know what the interface needs, puzzles, etc
//			//If a key is pressed then see if there is an active interface and call that objects on_keypress action
//			//Maybe interface components have an interfaceEventList that has all of the events that do NOT control the player
//
//
//
//			switch (inputEvent.event.type)
//			{
//				//case SDL_KEYUP:
//				case SDL_KEYDOWN:
//
//					////Interaction Keys
//					//if (keyScanCode == SDL_SCANCODE_E || keyScanCode == SDL_SCANCODE_R)
//					//{
//					//	action = actionComponent->getAction(ACTION_INTERACT);
//					//	action->perform(parent(), keyScanCode);
//					//}
//
//					break;
//				case SDL_MOUSEBUTTONDOWN:
//					
//
//
//
//					if(m_state.test(PlayerState::sprinting) == false){
//
//						//if (mouseButtons & SDL_BUTTON_LMASK) {
//						//	action = actionComponent->getAction(Actions::USE);
//						//	action->perform(parent(), Actions::USAGE);
//						//}
//					}
//					break;
//
//				default:
//					break;
//			}
//
//		}
//	}
//}




