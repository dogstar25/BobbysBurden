#include "BBGame.h"
#include "GameConstants.h"
#include "BBContextManager.h"

using namespace std::chrono_literals;

bool BBGame::init(
	std::shared_ptr<ContactListener> contactListener, std::shared_ptr<ContactFilter> contactFilter,
	std::shared_ptr<ComponentFactory> componentFactory, std::shared_ptr<ActionFactory> actionFactory, 
	std::shared_ptr<ParticleEffectsFactory> particleEffectsFactory,	std::shared_ptr<CutSceneFactory> cutSceneFactory, 
	std::shared_ptr<IMGuiFactory> iMGuiFactory, std::shared_ptr<TriggerFactory> triggerFactory, 
	std::shared_ptr<PuzzleFactory> puzzleFactory, std::shared_ptr<ContextManager> contextManager,
	std::shared_ptr<EnumMap> enumMap, std::shared_ptr<ColorMap> colorMap)
{

	Game::init(contactListener, contactFilter, componentFactory, actionFactory, particleEffectsFactory, cutSceneFactory, iMGuiFactory, triggerFactory, 
		puzzleFactory, contextManager, enumMap, colorMap);

	m_gameState = GameState::PLAY;

	//Init font library
	TTF_Init();

	//Initialize the texture manager
	m_renderer->init(m_window);

	//Initialize IMGUI
	ImGui::MobyDickInit(this);

	//Display basic loading message
	_displayLoadingMsg();

	TextureManager::instance().init();
	TextureManager::instance().load("textureAtlasAssets");

	//Initialize the SceneManager
	SceneManager::instance().init();
	SceneManager::instance().load("gameScenes");

	_displayLoadingMsg();

	//Initialize the Game Object Manager
	GameObjectManager::instance().init();
	GameObjectManager::instance().load("gameObjectDefinitions/houseObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/playerObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/commonObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/guiObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/lightObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/householdObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/bobbysObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/containerObjects");

	_displayLoadingMsg();

	//Initialize the sound manager
	SoundManager::instance().initSound();

	//Load a first scene
	Scene& scene = SceneManager::instance().pushScene("SCENE_PLAY");
	//scene.loadLevel("front1");
	scene.loadLevel("full_interior");

	//Add Inventory to all inventory objects
	//Figure out a place to put this custom game type stuff later
	const auto& player = scene.getFirstGameObjectByTrait(TraitTag::player);
	const auto& playerInventory = player->get()->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);
	auto gameObject = scene.addGameObject("OIL_CAN", GameLayer::FOREGROUND_5, (float)-50, (float)-50, (float)0);
	auto inventoryObject = scene.getGameObject(gameObject->id());

	playerInventory->addItem(inventoryObject.value());

	


	//Initialize the clock object
	Clock::instance().init();


	


	return true;
}

