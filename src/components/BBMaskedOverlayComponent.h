#pragma once
#include "MobyDick.h"


class BBMaskedOverlayComponent : public MaskedOverlayComponent
{

public:
	BBMaskedOverlayComponent() = default;
	BBMaskedOverlayComponent(Json::Value definitionJSON, GameObject* parent, Scene* parentScene);
	~BBMaskedOverlayComponent() = default;

	void update() override;

private:



};

