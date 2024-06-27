#pragma once
#include "MobyDick.h"

class Scene;

class BBComponentFactory : public ComponentFactory
{

public:


private:
	//Create version that has ALL possible inputs
	std::shared_ptr<Component> create(
		Json::Value definitionJSON,
		GameObject* parent,
		std::string gameObjectName,
		std::string gameObjectTextType,
		Scene* scene,
		float xMapPos,
		float yMapPos,
		float angleAdjust,
		b2Vec2 sizeOverride,
		const int componentType) override;

};

