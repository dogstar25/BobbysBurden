#pragma once
#include "MobyDick.h"

enum class CaughtPhase {
	FADING_TO_BLACK,
	RESTORING_STATE,
	FADING_FROM_BLACK
};

class BBCutSceneCaught : public CutScene
{

public:

	BBCutSceneCaught() = default;

	void run(Scene* scene) override;
	void start() override;
	void update() override;
	void end() override;
	void render() override;

private:

	void _restorePlayerToRoom();
	void _scatterInventory();

	CaughtPhase m_phase{ CaughtPhase::FADING_TO_BLACK };
	Timer m_fadeTimer{ 1.5f, false };
	Uint8 m_overlayAlpha{ 0 };

};
