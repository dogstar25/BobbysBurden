#pragma once
#include "MobyDick.h"

class BBInterfaceComponent : public InterfaceComponent
{
public:
	BBInterfaceComponent(Json::Value definitionJSON, Scene* parentScene);
	~BBInterfaceComponent() = default;

	virtual void setCursor(GameObject* gameObject, bool isMouseOver) override;
	void postInit() override;
	void handleDragging() override;
	virtual bool isEventAvailable(int eventId) override;

private:
	std::map<int, std::string> m_dependentPuzzles{};

};

