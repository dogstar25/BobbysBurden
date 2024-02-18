#pragma once
#include "MobyDick.h"


class BBMaskedOverlayComponent : public MaskedOverlayComponent
{

public:
	BBMaskedOverlayComponent() = default;
	BBMaskedOverlayComponent(Json::Value definitionJSON, Scene* parentScene);
	~BBMaskedOverlayComponent() = default;

	void update() override;

private:

	bool _hasLineOfSight(SDL_FPoint playerLocation, SDL_FPoint maskLocation);


};

