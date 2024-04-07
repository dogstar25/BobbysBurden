#include "BBComponentFactory.h"
#include "GameConstants.h"
#include "components/BobbyPlayerControlComponent.h"
#include "components/BBInterfaceComponent.h"
#include "components/BBStateComponent.h"
#include "components/BBMaskedOverlayComponent.h"
#include "components/BBEnvironmentComponent.h"

std::shared_ptr<Component> BBComponentFactory::create(
	Json::Value definitionJSON,
	std::string gameObjectName,
	std::string gameObjectTextType,
	Scene* scene,
	float xMapPos,
	float yMapPos,
	float angleAdjust,
	b2Vec2 sizeOverride,
	const int componentType)
{
	std::shared_ptr<Component> component{};
	auto gameObjectType = definitionJSON["type"].asString();
	Json::Value componentJSON{};

	//Handle game specific componenets, otherwise call the base ComponentFactory 'create'
	if (componentType == ComponentTypes::BOBBY_PLAYER_CONTROL_COMPONENT) {
		componentJSON = util::getComponentConfig(definitionJSON, ComponentTypes::BOBBY_PLAYER_CONTROL_COMPONENT);
		component = std::make_shared<BobbyPlayerControlComponent>(componentJSON);
	}
	else if (componentType == ComponentTypes::BB_INTERFACE_COMPONENT) {
		componentJSON = util::getComponentConfig(definitionJSON, ComponentTypes::BB_INTERFACE_COMPONENT);
		component = std::make_shared<BBInterfaceComponent>(componentJSON, scene);
	}
	else if (componentType == ComponentTypes::BB_STATE_COMPONENT) {
		componentJSON = util::getComponentConfig(definitionJSON, ComponentTypes::BB_STATE_COMPONENT);
		component = std::make_shared<BBStateComponent>(componentJSON);
	}
	else if (componentType == ComponentTypes::BB_MASKED_OVERLAY_COMPONENT) {
		componentJSON = util::getComponentConfig(definitionJSON, ComponentTypes::BB_MASKED_OVERLAY_COMPONENT);
		component = std::make_shared<BBMaskedOverlayComponent>(componentJSON, scene);
	}
	else if (componentType == ComponentTypes::BB_ENVIRONMENT_COMPONENT) {
		componentJSON = util::getComponentConfig(definitionJSON, ComponentTypes::BB_ENVIRONMENT_COMPONENT);
		component = std::make_shared<BBEnvironmentComponent>(componentJSON);
	}

	else {
		component = ComponentFactory::create(
			definitionJSON,
			gameObjectName,
			gameObjectTextType,
			scene,
			xMapPos,
			yMapPos,
			angleAdjust,
			sizeOverride,
			componentType);
	}

    return component;
}
