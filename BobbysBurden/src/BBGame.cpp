#include "BBGame.h"
#include "GameConstants.h"
#include "BBContextManager.h"

using namespace std::chrono_literals;

bool BBGame::init(
	std::shared_ptr<ContactListener> contactListener, 
	std::shared_ptr<ContactFilter> contactFilter,
	std::shared_ptr<ComponentFactory> componentFactory, 
	std::shared_ptr<ActionFactory> actionFactory, 
	std::shared_ptr<ParticleEffectsFactory> particleEffectsFactory,	
	std::shared_ptr<CutSceneFactory> cutSceneFactory, 
	std::shared_ptr<IMGuiFactory> iMGuiFactory, 
	std::shared_ptr<TriggerFactory> triggerFactory, 
	std::shared_ptr<PuzzleFactory> puzzleFactory, 
	std::shared_ptr<EnvironmentEventFactory> environmentEventFactory,
	std::shared_ptr<ContextManager> contextManager,
	std::shared_ptr<GameStateManager> gameStateManager,
	std::shared_ptr<EnumMap> enumMap, 
	std::shared_ptr<ColorMap> colorMap
)
{

	//Assign all of the game specific managers and factories to the main game object
	Game::init(
		contactListener, contactFilter, componentFactory, actionFactory, particleEffectsFactory, cutSceneFactory, iMGuiFactory, triggerFactory, 
		puzzleFactory, environmentEventFactory, contextManager, gameStateManager, enumMap, colorMap
	);

	m_gameState = GameState::PLAY;

	//Init font library
	//WE NEED THIS FOR PRE-EVERYTHING TO SHOW BASIC TEXT ON THE SCREEN
	//for the "Loading..." text display
	TTF_Init();

	//Initialize the texture manager
	m_renderer->init(m_window);

	//Initialize IMGUI
	ImGui::MobyDickInit(this);

	//Display basic loading message
	_displayLoadingMsg();

	//Load all textures
	TextureManager::instance().loadTextures("textureAtlas00");
	TextureManager::instance().loadTextures("textureAtlas01");
	TextureManager::instance().loadTextures("textureAtlas02");
	TextureManager::instance().loadTextures("textureAtlas03");
	TextureManager::instance().loadTextures("textureAtlas04");
	TextureManager::instance().loadTextures("textureAtlas05");
	TextureManager::instance().loadTextures("textureAtlas06");
	TextureManager::instance().loadTextures("textureAtlas99");
	TextureManager::instance().loadBlueprints("blueprintAssets");
	TextureManager::instance().loadFonts("fontAssets");
	TextureManager::instance().loadCursors("mouseCursors");

	//Initialize the SceneManager
	SceneManager::instance().init();
	SceneManager::instance().load("gameScenes");

	_displayLoadingMsg();

	//Initialize the Game Object Manager
	GameObjectManager::instance().init();
	GameObjectManager::instance().load("gameObjectDefinitions/commonObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/houseObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/playerObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/guiObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/lightObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/householdObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/bobbysRoomFurniture");
	GameObjectManager::instance().load("gameObjectDefinitions/drawerObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/shelfObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/particleObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/doorObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/environmentObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/frontRooms");
	GameObjectManager::instance().load("gameObjectDefinitions/backRooms");
	GameObjectManager::instance().load("gameObjectDefinitions/detachedRooms");
	GameObjectManager::instance().load("gameObjectDefinitions/lightFixtureObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/wallBackgroundObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/puzzleObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/puzzlePieceObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/enemyObjects");
	GameObjectManager::instance().load("gameObjectDefinitions/furnitureObjects");

	//GameObjectManager::instance().load("gameObjectDefinitions/testObjects");

	_displayLoadingMsg();

	//Initialize the sound manager
	SoundManager::instance().initSound();

	//Load a first scene
	Scene& scene = SceneManager::instance().pushScene("SCENE_PLAY");
	//Scene& scene = SceneManager::instance().pushScene("SCENE_TEST");

	scene.loadLevel("full_interior");

	//////////////////////////////////////////////////////
	//Force the load of the new game primer file for now
	//This will latyer come from the splash screen New Game button
	//Initialize the saveFile
	gameStateManager->initializeGameDataFile();

	//gameStateManager->loadGamePrimerFile();


	////////////////////////////////////////////////

	//Load the game Settings
	contextManager->loadSettings();
	
	//Figure out a place to put this custom game type stuff later
	const auto& player = scene.getFirstGameObjectByTrait(TraitTag::player);
	const auto& playerInventory = player->get()->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);
	playerInventory->addItem("RUBY");
	playerInventory->addItem("EMERALD");
	playerInventory->addItem("DIAMOND");
	playerInventory->addItem("SAPHIRE");

	auto action = actionFactory->create("ToggleBobbyInventory", Json::Value{}, player->get());
	action->perform(player->get());

	const auto& topDrawer = scene.getFirstGameObjectByName("BOBBY_SIDETABLE_TOP_DRAWER");
	const auto& topDrawerInventory = topDrawer->get()->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);
	topDrawerInventory->addItem("BOTTLE1");

	////Dresser Shelf
	const auto& dresserShelf = scene.getFirstGameObjectByName("BOBBY_DRESSER_SHELF");
	const auto& dresserShelfInventory = dresserShelf->get()->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);
	dresserShelfInventory->addItem("OIL_CAN");
	dresserShelfInventory->addItem("PAPER_BALLOON");
	dresserShelfInventory->refreshInventoryDisplay();

	const auto& denBookshelf = scene.getFirstGameObjectByName("denBookcaseShelf");
	const auto& denBookshelfInventory = denBookshelf->get()->getComponent<InventoryComponent>(ComponentTypes::INVENTORY_COMPONENT);
	denBookshelfInventory->addItem("BOOK_SEALIFE");

	//Initialize the clock object
	Clock::instance().init();

	return true;
}

