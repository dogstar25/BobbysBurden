#pragma once
#include "MobyDick.h"

class BBInterfaceComponent : public InterfaceComponent
{
public:
	BBInterfaceComponent(Json::Value definitionJSON, GameObject* parent, Scene* parentScene);
	~BBInterfaceComponent() = default;

	virtual void render() override;
	virtual bool isDraggingAllowed() override;
	virtual bool isEventAvailable(int eventId) override;
	virtual bool doesInterfaceHavePriority(std::bitset<MAX_EVENT_STATES> eventState) override;
	//virtual bool shouldInterfaceMenuBeShown(std::bitset<(int)InterfaceEvents::COUNT> eventState) override;
	void clearCurrentGameObjectInterfaceActive() { m_currentGameObjectInterfaceActive = std::nullopt; }
	std::optional<GameObject*> currentGameObjectInterfaceActive() {
		return m_currentGameObjectInterfaceActive;
	}
	
	static std::optional<std::shared_ptr<GameObject>> determineItemContactInterfaceTarget(GameObject* itemObject);

private:
	std::map<int, std::string> m_dependentPuzzles{};

	////////Static Variables
	
	static inline std::optional<GameObject*> m_currentDraggingObject{};

	///////////////////////


};

