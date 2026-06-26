#include "BBCutSceneCaught.h"


void BBCutSceneCaught::run(Scene* scene)
{
	currentScene = scene;

	if (currentState == cutSceneState::IDLE) {
		start();
	}
	else if (currentState == cutSceneState::RUNNING) {
		update();
	}
}

void BBCutSceneCaught::start()
{
	currentState = cutSceneState::RUNNING;

	auto player = currentScene->player();
	player->getComponent<PlayerControlComponent>(ComponentTypes::PLAYER_CONTROL_COMPONENT)->disable();

	m_phase = CaughtPhase::FADING_TO_BLACK;
	m_overlayAlpha = 0;
	m_fadeTimer.reset();
}

void BBCutSceneCaught::update()
{

	if (m_phase == CaughtPhase::FADING_TO_BLACK) {

		m_overlayAlpha = static_cast<Uint8>(255.f * m_fadeTimer.percentTargetMet());

		if (m_fadeTimer.hasMetTargetDuration()) {
			m_overlayAlpha = 255;
			m_phase = CaughtPhase::RESTORING_STATE;
		}

	}
	else if (m_phase == CaughtPhase::RESTORING_STATE) {

		_restorePlayerToRoom();
		_scatterInventory();

		m_fadeTimer.reset();
		m_phase = CaughtPhase::FADING_FROM_BLACK;

	}
	else if (m_phase == CaughtPhase::FADING_FROM_BLACK) {

		m_overlayAlpha = static_cast<Uint8>(255.f * (1.0f - m_fadeTimer.percentTargetMet()));

		if (m_fadeTimer.hasMetTargetDuration()) {
			m_overlayAlpha = 0;
			end();
		}

	}

}

void BBCutSceneCaught::end()
{
	auto player = currentScene->player();
	player->getComponent<PlayerControlComponent>(ComponentTypes::PLAYER_CONTROL_COMPONENT)->enable();

	util::sendSceneEvent(SCENE_ACTION_RELEASE_DIRECT);
}

void BBCutSceneCaught::render()
{
	if (m_overlayAlpha == 0) {
		return;
	}

	SDL_Renderer* sdlRenderer = game->renderer()->sdlRenderer();
	SDL_SetRenderDrawBlendMode(sdlRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, m_overlayAlpha);
	SDL_RenderFillRect(sdlRenderer, nullptr);
}

void BBCutSceneCaught::_restorePlayerToRoom()
{

	auto player = currentScene->player();
	auto physicsComp = player->getComponent<PhysicsComponent>(ComponentTypes::PHYSICS_COMPONENT);

	SDL_FPoint spawnPoint = currentScene->playerOriginalSpawnPoint();
	b2Vec2 spawnB2 = { spawnPoint.x, spawnPoint.y };
	util::toBox2dPoint(spawnB2);

	b2Body_SetTransform(physicsComp->physicsBodyId(), spawnB2,
		b2Body_GetRotation(physicsComp->physicsBodyId()));
	b2Body_SetLinearVelocity(physicsComp->physicsBodyId(), { 0.f, 0.f });

}

void BBCutSceneCaught::_scatterInventory()
{

	auto player = currentScene->player();
	auto playerInv = player->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);

	// Collect item types before clearing
	std::vector<std::string> itemTypes;
	for (auto& item : playerInv->items()) {
		if (item.has_value()) {
			itemTypes.push_back(item.value()->type());
		}
	}

	playerInv->clearInventory();

	if (itemTypes.empty()) {
		return;
	}

	// Find all containers in the scene
	auto containers = currentScene->getGameObjectsByTrait(TraitTag::receptacle);

	std::vector<std::shared_ptr<GameObject>> validContainers;
	for (auto& container : containers) {
		if (container->hasComponent(ComponentTypes::INVENTORY_COMPONENT)) {
			validContainers.push_back(container);
		}
	}

	if (validContainers.empty()) {
		return;
	}

	auto seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
	std::default_random_engine rng(seed);

	for (auto& itemType : itemTypes) {

		std::shuffle(validContainers.begin(), validContainers.end(), rng);

		for (auto& container : validContainers) {
			auto inv = container->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);
			if (!inv->isFull()) {
				inv->addItem(itemType);
				break;
			}
		}

	}

}
